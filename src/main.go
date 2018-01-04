package main

import (
	"archive/tar"
	"bufio"
	"compress/gzip"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
	"time"

	bolt "github.com/coreos/bbolt"
	"github.com/gin-gonic/gin"
	"github.com/jtblin/go-ldap-client"
)

const (
	bucketName      = "log"
	dbPath          = "/home/jeremy.chang/log.db"
	psBinPath       = "/home/jeremy.chang/pspro_lin64/bin"
	licensePath     = "/home/jeremy.chang/license"
	exampleFilePath = "/home/jeremy.chang/files"
)

// ReqForm - Bind request form from JSON
type ReqForm struct {
	Username string `form:"username" json:"username" binding:"required"`
	Passwd   string `form:"passwd" json:"passwd" binding:"required"`
	DueDate  int    `form:"due" json:"due" binding:"required"`
}

// GenLog - Struct of log
type GenLog struct {
	ID          int    `json:"id"`
	UID         string `json:"uid"`
	Name        string `json:"name"`
	Action      string `json:"action"`
	CreatedTime int64  `json:"created_time"`
}

func main() {
	r := gin.Default()
	r.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})

	r.POST("/genlicense", genLicense)
	r.GET("/dl/:uid", dlLicense)
	r.GET("/log", getGenLog)

	r.Run()
}

func genLicense(c *gin.Context) {
	var jsonReqForm ReqForm

	c.Bind(&jsonReqForm)

	ldapClient := &ldap.LDAPClient{
		Base:        "dc=viscovery,dc=com",
		Host:        "192.168.7.252",
		Port:        389,
		UseSSL:      false,
		BindDN:      "uid=ldapadmin,cn=users,dc=viscovery,dc=com",
		UserFilter:  "(uid=%s)",
		GroupFilter: "(memberUid=%s)",
		Attributes:  []string{"givenName", "sn", "mail", "uid", "uidNumber"},
	}
	defer ldapClient.Close()

	username := jsonReqForm.Username
	passwd := jsonReqForm.Passwd

	duedate := jsonReqForm.DueDate
	if duedate == 0 {
		duedate = 7
	}

	ok, user, err := ldapClient.Authenticate(username, passwd)
	if err != nil {
		errMsg := fmt.Sprintf("Error authenticating user %s: %+v", username, err)
		c.JSON(http.StatusForbidden, gin.H{
			"error": errMsg,
		})

		return
	}
	if !ok {
		errMsg := fmt.Sprintf("Authenticating failed for user %s", username)
		c.JSON(http.StatusForbidden, gin.H{
			"error": errMsg,
		})

		return
	}

	dtCmd := fmt.Sprintf("%s/sggendate", psBinPath)
	dt, err := exec.Command(dtCmd, strconv.Itoa(duedate)).Output()
	if err != nil {
		errMsg := fmt.Sprintf("%s", err)
		c.JSON(http.StatusInternalServerError, gin.H{
			"command": dtCmd,
			"error":   errMsg,
		})

		return
	}
	dtStr := strings.TrimSuffix(string(dt), "\n")

	licCmd := fmt.Sprintf("%s/pskeycode", psBinPath)
	lic, err := exec.Command(licCmd, "sha256", "monitor", "5.0", "dev", "any", dtStr).Output()
	if err != nil {
		errMsg := fmt.Sprintf("%s", err)
		c.JSON(http.StatusInternalServerError, gin.H{
			"command": licCmd,
			"dt":      dtStr,
			"error":   errMsg,
		})

		return
	}

	_ = os.MkdirAll(filepath.Join(licensePath, user["uidNumber"]), 0755)
	f, err := os.Create(filepath.Join(licensePath, user["uidNumber"], "monitor.lic"))
	if err != nil {
		result := fmt.Sprintf("User: %+v, License: %s", user, lic)
		c.JSON(http.StatusOK, gin.H{
			"result": result,
		})

		return
	}
	defer f.Close()

	w := bufio.NewWriter(f)
	_, err = w.Write(lic)
	err = w.Flush()
	if err != nil {
		result := fmt.Sprintf("User: %+v, License: %s", user, lic)
		c.JSON(http.StatusOK, gin.H{
			"result": result,
		})

		return
	}

	tarFile, err := os.Create(filepath.Join(licensePath, user["uidNumber"]+".tar.gz"))
	if err != nil {
		result := fmt.Sprintf("User: %+v, License: %s", user, lic)
		c.JSON(http.StatusOK, gin.H{
			"result": result,
		})

		return
	}
	defer tarFile.Close()

	gw := gzip.NewWriter(tarFile)
	defer gw.Close()
	tw := tar.NewWriter(gw)
	defer tw.Close()

	files := []string{
		filepath.Join(exampleFilePath, "Nodelocked.py"),
		filepath.Join(exampleFilePath, "PSProlibProxy.pyc"),
		filepath.Join(exampleFilePath, "_PSProlibProxy.so"),
		filepath.Join(licensePath, user["uidNumber"], "monitor.lic"),
	}

	for i := range files {
		if err := addFile(tw, files[i]); err != nil {
			log.Fatalln(err)
		}
	}

	os.RemoveAll(filepath.Join(licensePath, user["uidNumber"]))

	writeLog(user["uidNumber"], user["sn"], "GEN")

	c.JSON(http.StatusOK, gin.H{
		"licenseDLPath": c.Request.Host + "/dl/" + user["uidNumber"],
	})
}

func dlLicense(c *gin.Context) {
	uid := c.Param("uid")

	writeLog(uid, "", "DL")

	c.Header("Content-Description", "File Transfer")
	c.Header("Content-Transfer-Encoding", "binary")
	c.Header("Content-Disposition", "attachment; filename="+uid+".tar.gz")
	c.Header("Content-Type", "application/octet-stream")
	c.File(filepath.Join(licensePath, uid+".tar.gz"))
}

func copyFile(src, dest string) {
	srcFile, err := os.Open(src)
	checkErr(err)
	defer srcFile.Close()

	destFile, err := os.Create(dest)
	checkErr(err)
	defer destFile.Close()

	_, err = io.Copy(destFile, srcFile)
	checkErr(err)

	err = destFile.Sync()
	checkErr(err)
}

func addFile(tw *tar.Writer, p string) error {
	f, err := os.Open(p)
	if err != nil {
		return err
	}
	defer f.Close()

	if stat, err := f.Stat(); err == nil {
		// now lets create the header as needed for this file within the tarball
		header := new(tar.Header)
		header.Name = filepath.Base(p)
		header.Size = stat.Size()
		header.Mode = int64(stat.Mode())
		header.ModTime = stat.ModTime()
		// write the header to the tarball archive
		if err := tw.WriteHeader(header); err != nil {
			return err
		}
		// copy the file data to the tarball
		if _, err := io.Copy(tw, f); err != nil {
			return err
		}
	}

	return nil
}

func writeLog(uid, name, action string) {
	db, err := bolt.Open(dbPath, 0600, nil)
	checkErr(err)
	defer db.Close()

	err = db.Update(func(tx *bolt.Tx) error {
		b, err := tx.CreateBucketIfNotExists([]byte(bucketName))
		if err != nil {
			return err
		}

		id, _ := b.NextSequence()

		genLog := &GenLog{
			ID:          int(id),
			UID:         uid,
			Name:        name,
			Action:      action,
			CreatedTime: time.Now().Unix(),
		}

		encoded, err := json.Marshal(genLog)
		if err != nil {
			return err
		}

		return b.Put(itob(int(id)), encoded)
	})

	checkErr(err)
}

func getGenLog(c *gin.Context) {
	db, err := bolt.Open(dbPath, 0600, nil)
	checkErr(err)
	defer db.Close()

	var results []GenLog
	var result GenLog

	err = db.View(func(tx *bolt.Tx) error {
		b := tx.Bucket([]byte(bucketName))

		b.ForEach(func(k, v []byte) error {
			err := json.Unmarshal(v, &result)

			log.Printf("%+v", result)
			results = append(results, result)

			return err
		})

		return nil
	})

	checkErr(err)

	c.JSON(http.StatusOK, results)
}

func checkErr(err error) {
	if err != nil {
		log.Fatalln(err)
	}
}

func itob(v int) []byte {
	b := make([]byte, 8)
	binary.BigEndian.PutUint64(b, uint64(v))
	return b
}
