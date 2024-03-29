BINARY = go-gen-safeguard-license
VET_REPORT = vet.report
TEST_REPORT = tests.xml
GOARCH = amd64

VERSION?=?
COMMIT=$(shell git rev-parse HEAD)
BRANCH=$(shell git rev-parse --abbrev-ref HEAD)

# Symlink into GOPATH
GITHUB_USERNAME=mrmoneyc
BUILD_DIR=${GOPATH}/src/github.com/${GITHUB_USERNAME}/${BINARY}
CURRENT_DIR=$(shell pwd)
BUILD_DIR_LINK=$(shell readlink ${BUILD_DIR})

# Setup the -ldflags option for go build here, interpolate the variable values
LDFLAGS = -ldflags "-X main.VERSION=${VERSION} -X main.COMMIT=${COMMIT} -X main.BRANCH=${BRANCH}"

# Deploy target
DEPLOY_SRV_IP = 192.168.78.242
DEPLOY_SRV_USER = jeremy.chang

# Build the project
all: link clean test vet linux darwin windows

link:
	BUILD_DIR=${BUILD_DIR}; \
		  BUILD_DIR_LINK=${BUILD_DIR_LINK}; \
		  CURRENT_DIR=${CURRENT_DIR}; \
		  if [ "$${BUILD_DIR_LINK}" != "$${CURRENT_DIR}" ]; then \
		  echo "Fixing symlinks for build"; \
		  rm -f $${BUILD_DIR}; \
		  ln -s $${CURRENT_DIR} $${BUILD_DIR}; \
		  fi

linux:
	cd ${BUILD_DIR}; \
		GOOS=linux GOARCH=${GOARCH} ENABLE_CGO=0 go build ${LDFLAGS} -o ${BINARY}-linux-${GOARCH} . ; \
		cd - >/dev/null

darwin:
	cd ${BUILD_DIR}; \
		GOOS=darwin GOARCH=${GOARCH} go build ${LDFLAGS} -o ${BINARY}-darwin-${GOARCH} . ; \
		cd - >/dev/null

windows:
	cd ${BUILD_DIR}; \
		GOOS=windows GOARCH=${GOARCH} go build ${LDFLAGS} -o ${BINARY}-windows-${GOARCH}.exe . ; \
		cd - >/dev/null

test:
	if ! hash go2xunit 2>/dev/null; then go install github.com/tebeka/go2xunit; fi
	cd ${BUILD_DIR}; \
		godep go test -v ./... 2>&1 | go2xunit -output ${TEST_REPORT} ; \
		cd - >/dev/null

vet:
	-cd ${BUILD_DIR}; \
		godep go vet ./... > ${VET_REPORT} 2>&1 ; \
		cd - >/dev/null

fmt:
	cd ${BUILD_DIR}; \
		go fmt $$(go list ./... | grep -v /vendor/) ; \
		cd - >/dev/null

clean:
	-rm -f ${TEST_REPORT}
	-rm -f ${VET_REPORT}
	-rm -f ${BINARY}-*

deploy:
	rsync -av -e 'ssh' go-gen-safeguard-license-linux-amd64 ${DEPLOY_SRV_USER}@${DEPLOY_SRV_IP}:~/go-gen-safeguard-license-linux-amd64
	rsync -av -e 'ssh' public ${DEPLOY_SRV_USER}@${DEPLOY_SRV_IP}:~/

.PHONY: link linux darwin windows test vet fmt clean deploy
