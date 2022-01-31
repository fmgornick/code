#!/bin/bash

PORT=$1

if [ -z "$1" ]
then
    PORT=8081
fi

ROOTDIR=`git rev-parse --show-toplevel`
source ${ROOTDIR}/config/settings

if [ $OSTYPE == "msys" ] # if we're using Git bash, we need an extra little somthing
then
  WINPTY="winpty -Xallow-non-tty"
  ROOTDIR="/${ROOTDIR}"
fi

$WINPTY docker run --rm -p 127.0.0.1:$PORT:8081 -v "${ROOTDIR}:/home/user/repo" -it ${DOCKER_IMAGE_PREFIX}/env
