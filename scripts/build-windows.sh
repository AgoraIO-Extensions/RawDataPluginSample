#!/usr/bin/env bash

set -e
set -x

IRIS_EVENT_DIR=$1
OUT_DIR=$2

BUILD_TYPE="Release"

if [ ! -d "$IRIS_EVENT_DIR/build/windows/x64" ]; then
    mkdir -p $IRIS_EVENT_DIR/build/windows/x64
fi

pushd $IRIS_EVENT_DIR/build/windows/x64
cmake \
  -G "Visual Studio 16 2019" \
  -A x64 \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  "$IRIS_EVENT_DIR"
cmake --build . --config "$BUILD_TYPE"
popd

ls ${IRIS_EVENT_DIR}/build/windows/x64/$BUILD_TYPE
cp -RP "${IRIS_EVENT_DIR}/build/windows/x64/$BUILD_TYPE/VideoObserverPlugin.dll" "${OUT_DIR}/VideoObserverPlugin.dll"