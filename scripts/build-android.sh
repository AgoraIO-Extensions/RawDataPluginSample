#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/.."

build() {
  cd "$root_path" || exit
  mkdir -p ./build/android/"$1"
  cd ./build/android/"$1" || exit
  cmake \
    -G "Ninja" \
    -DANDROID_ABI="$1" \
    -DANDROID_NDK="$ANDROID_NDK" \
    -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK"/build/cmake/android.toolchain.cmake \
    -DANDROID_TOOLCHAIN=clang \
    -DANDROID_PLATFORM=android-16 \
    -DCMAKE_BUILD_TYPE="$2" \
    -DIRIS_SDK_TYPE="$3" \
    "$root_path"
  cmake --build . --config "$2"
}

buildALL() {
  buildType="$1"
  buildTypeLower=$(echo "$buildType" | tr '[:upper:]' '[:lower:]')
  cd "$root_path"/platform/android || exit
  echo "start build aar ----------"
  sh ./gradlew assemble"$buildType"
  echo "start copy outputs ----------"
  output_dir="$root_path/build/android/ALL_ARCHITECTURE/output/$buildType"
  output_name="AgoraRawDataPlugin"
  mkdir -p "$output_dir"
  cp "$root_path"/android/build/outputs/aar/android-"$buildTypeLower".aar "$output_dir/$output_name.aar"
  cp "$root_path"/android/build/intermediates/aar_main_jar/"$buildTypeLower"/classes.jar "$output_dir/$output_name.jar"
  mkdir -p "$output_dir/arm64-v8a"
  cp -rp "$root_path"/android/.cxx/cmake/"$buildTypeLower"/arm64-v8a/output/"$buildType"/ "$output_dir/arm64-v8a/"
  mkdir -p "$output_dir/armeabi-v7a"
  cp -rp "$root_path"/android/.cxx/cmake/"$buildTypeLower"/armeabi-v7a/output/"$buildType"/ "$output_dir/armeabi-v7a/"
  mkdir -p "$output_dir/x86"
  cp -rp "$root_path"/android/.cxx/cmake/"$buildTypeLower"/x86/output/"$buildType"/ "$output_dir/x86/"
  mkdir -p "$output_dir/x86_64"
  cp -rp "$root_path"/android/.cxx/cmake/"$buildTypeLower"/x86_64/output/"$buildType"/ "$output_dir/x86_64/"
}

if [ "$1" = "build" ]; then
  build "$2" "$3"
elif [ "$1" = "buildALL" ]; then
  buildALL "$2"
else
  buildALL Release
fi
