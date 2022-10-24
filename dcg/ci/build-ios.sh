#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/../.."

build() {
  cd "$root_path" || exit
  mkdir -p ./build/ios/"$1"
  cd ./build/ios/"$1" || exit
  if [ "$1" = "OS64COMBINED" ]; then
    archs="armv7 arm64"
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
    -DIRIS_SDK_TYPE="$3" \
    "$root_path"
  cmake --build . --config "$2"
  unset archs
}

buildALL() {
  buildType="$1"
  sdkType="$2"
  echo "start build OS64COMBINED ----------"
  build OS64COMBINED "$buildType" "$sdkType"
  echo "start build SIMULATOR64 ----------"
  build SIMULATOR64 "$buildType" "$sdkType"
  echo "start create .xcframework ----------"
  output_dir="$root_path/build/ios/ALL_ARCHITECTURE/output/dcg/$buildType"
  physical_output_dir="$root_path/build/ios/OS64COMBINED/output/dcg/$buildType"
  simulator_output_dir="$root_path/build/ios/SIMULATOR64/output/dcg/$buildType"
  output_name="AgoraRtcWrapper"
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
  sdkType="$4"
  build "$2" "$3" "${sdkType:=Video}"
elif [ "$1" = "buildALL" ]; then
  sdkType="$3"
  buildALL "$2" "${sdkType:=Video}"
else
  sdkType="$1"
  buildALL Release "${sdkType:=Video}"
fi
