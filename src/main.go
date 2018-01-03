package main

import (
	"fmt"
	"net/http"
	"os/exec"

	"github.com/gin-gonic/gin"
	"github.com/jtblin/go-ldap-client"
)

const (
	psBinPath = "/opt/genlicense/bin"
)

// ReqForm - Bind login info from JSON
type ReqForm struct {
	Username string `form:"username" json:"username" binding:"required"`
	Passwd   string `form:"passwd" json:"passwd" binding:"required"`
	dueDate  string `form:"duedate" json:"duedate" binding:"required"`
}

func main() {
	r := gin.Default()

	r.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})

	r.POST("/genlicense", genLicense)

	r.Run()
}

func genLicense(c *gin.Context) {
	var jsonReqForm ReqForm

	c.Bind(&jsonReqForm)

	ldapClient := &ldap.LDAPClient{
		Base:         "dc=viscovery,dc=com",
		Host:         "192.168.7.252",
		Port:         389,
		UseSSL:       false,
		BindDN:       "uid=ldapadmin,cn=users,dc=viscovery,dc=com",
		BindPassword: "123456",
		UserFilter:   "(uid=%s)",
		GroupFilter:  "(memberUid=%s)",
		Attributes:   []string{"givenName", "sn", "mail", "uid"},
	}
	defer ldapClient.Close()

	username := jsonReqForm.Username
	passwd := jsonReqForm.Passwd

	duedate := jsonReqForm.dueDate
	if duedate == "" {
		duedate = "7"
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
	dt, err := exec.Command(dtCmd, duedate).Output()
	if err != nil {
		errMsg := fmt.Sprintf("%s", err)
		c.JSON(http.StatusInternalServerError, gin.H{
			"command": dtCmd,
			"error":   errMsg,
		})

		return
	}

	licCmd := fmt.Sprintf("%s/pskeycode", psBinPath)
	lic, err := exec.Command(licCmd, "sha256", "monitor", "5.0", "dev", "any", string(dt)).Output()
	if err != nil {
		errMsg := fmt.Sprintf("%s", err)
		c.JSON(http.StatusInternalServerError, gin.H{
			"command": licCmd,
			"error":   errMsg,
		})

		return
	}

	result := fmt.Sprintf("User: %+v, License: %+v", user, lic)
	c.JSON(http.StatusOK, gin.H{
		"result": result,
	})
}
