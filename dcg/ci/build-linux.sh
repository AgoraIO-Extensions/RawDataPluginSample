#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/../.."

build() {
  cd "$root_path" || exit
  mkdir -p ./build/linux
  cd ./build/linux || exit
  cmake \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE="$1" \
    -DIRIS_SDK_TYPE=DCG \
    "$root_path"
  cmake --build . --config "$1"
}

if [ "$1" = "build" ]; then
  build "$2"
else
  echo "start build ----------"
  build Debug
  build Release
fi
