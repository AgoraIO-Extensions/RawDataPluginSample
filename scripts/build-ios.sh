#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/.."

build() {
  cd "$root_path" || exit
  mkdir -p ./build/ios/"$1"
  cd ./build/ios/"$1" || exit
  if [ "$1" = "OS64COMBINED" ]; then
    archs="arm64"
  elif [ "$1" = "SIMULATOR64" ]; then
    archs="arm64 x86_64"
  fi
  cmake \
    -G "Xcode" \
    -DCMAKE_TOOLCHAIN_FILE="$root_path"/cmake/ios.toolchain.cmake \
    -DPLATFORM="$1" \
    -DARCHS="$archs" \
    -DDEPLOYMENT_TARGET="9.0" \
    -DCMAKE_BUILD_TYPE="$2" \
    "$root_path"
  cmake --build . --config "$2"
  unset archs
}

buildALL() {
  buildType="$1"
  echo "start build OS64COMBINED ----------"
  build OS64COMBINED "$buildType"
  echo "start build SIMULATOR64 ----------"
  build SIMULATOR64 "$buildType"
  echo "start create .xcframework ----------"
  output_dir="$root_path/build/ios/ALL_ARCHITECTURE/output/$buildType"
  physical_output_dir="$root_path/build/ios/OS64COMBINED/output/$buildType"
  simulator_output_dir="$root_path/build/ios/SIMULATOR64/output/$buildType"
  output_name="AgoraRawDataPlugin"
  rm -rf "$output_dir"
  mkdir -p "$output_dir"
  xcodebuild -create-xcframework \
    -framework "$physical_output_dir/$output_name.framework" \
    -debug-symbols "$physical_output_dir/$output_name.framework.dSYM" \
    -framework "$simulator_output_dir/$output_name.framework" \
    -debug-symbols "$simulator_output_dir/$output_name.framework.dSYM" \
    -output "$output_dir/$output_name.xcframework"
  echo "start create .framework ----------"
  cp -rp "$physical_output_dir" "${output_dir%$buildType}"
  lipo -remove arm64 \
    "$simulator_output_dir/$output_name.framework/$output_name" \
    -output "$simulator_output_dir/$output_name.framework/$output_name"
  lipo -create \
    "$physical_output_dir/$output_name.framework/$output_name" \
    "$simulator_output_dir/$output_name.framework/$output_name" \
    -output "$output_dir/$output_name.framework/$output_name"
}

if [ "$1" = "build" ]; then
  build "$2" "$3"
elif [ "$1" = "buildALL" ]; then
  buildALL "$2"
else
  buildALL Release
fi
