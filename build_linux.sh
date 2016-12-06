#!/usr/bin/env bash

set -e -u -E # 子命令失败后会停止

WORK_DIR=`pwd`
BUILD_DIR=${WORK_DIR}/build/build_linux

if [ ! -d ${BUILD_DIR} ] ; then
    mkdir -p $BUILD_DIR
fi

cd ${BUILD_DIR}
cmake ../..
make 
cd -
