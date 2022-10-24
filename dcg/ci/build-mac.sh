#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/../.."

build() {
  cd "$root_path" || exit
  mkdir -p ./build/mac/"$1"
  cd ./build/mac/"$1" || exit
  archs="arm64 x86_64"
  cmake \
    -G "Xcode" \
    -DCMAKE_TOOLCHAIN_FILE="$root_path"/cmake/ios.toolchain.cmake \
    -DPLATFORM="$1" \
    -DARCHS="$archs" \
    -DCMAKE_BUILD_TYPE="$2" \
    -DIRIS_SDK_TYPE="$3" \
    "$root_path"
  cmake --build . --config "$2"
  unset archs
}

buildALL() {
  buildType="$1"
  sdkType="$2"
  echo "start build MAC ----------"
  build MAC "$buildType" "$sdkType"
}

if [ "$1" = "build" ]; then
  sdkType="$4"
  build "$2" "$3" "${sdkType:=Video}"
elif [ "$1" = "buildALL" ]; then
  sdkType="$3"
  buildALL "$2" "${sdkType:=Video}"
else
  sdkType="$1"
  buildALL Release "${sdkType:=Video}"
fi
