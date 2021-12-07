#!/bin/bash

ROOTDIR=`git rev-parse --show-toplevel`
source ${ROOTDIR}/config/settings

# this block checks if we're using git bash. If so, git bash (un)helpfully
# prepends any absolute path (something starting with a /) with C:/Program Files/Git/
# So, we need to remove any leading / to prevent git bash from prepending that
# annoying string. We remove leading / no matter what, then just add them back
# in the Dockerfile. However, the output of `git rev-parse --show-toplevel` when
# run in git bash doesn't start the absolute path with a /, so in the following
# if statement we only check to see if we're running on anything other than
# git bash, and if this is true, then remove the leading /.
if [ $OSTYPE != "msys" ]
then
	ROOTDIR="${ROOTDIR:1}"
	EXTRA_SLASH="/"
fi

DEP_DIR="${DEP_DIR:1}" # Always has a leading / that we need to remove
SRC_DIR="env"


echo ${ROOTDIR}
echo ${DEP_DIR}


docker build $1 \
	--target env \
	--build-arg USER_ID=$(id -u) \
	--build-arg GROUP_ID=$(id -g) \
	--build-arg DEP_DIR=${DEP_DIR} \
	--build-arg SRC_DIR=${SRC_DIR} \
	-t ${DOCKER_IMAGE_PREFIX}/${SRC_DIR} ${EXTRA_SLASH}${ROOTDIR}