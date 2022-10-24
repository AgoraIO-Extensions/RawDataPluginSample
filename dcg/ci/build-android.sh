#!/bin/bash

set -ex

shell_path=$(
  cd "$(dirname "$0")" || exit
  pwd
)
root_path="$shell_path/../.."

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
  sdkType="$2"
  cd "$shell_path"/../android
  echo "start build aar ----------"
  sh ./gradlew assemble"$buildType" -P"$sdkType" -Dhttps.proxyHost=10.80.1.174 -Dhttps.proxyPort=1080
  echo "start copy outputs ----------"
  output_dir="$root_path/build/android/ALL_ARCHITECTURE/output/dcg/$buildType"
  output_name="VideoObserverPlugin"
  mkdir -p "$output_dir"
  cp app/build/outputs/aar/app-"$buildTypeLower".aar "$output_dir/$output_name.aar"
  cp app/build/intermediates/aar_main_jar/"$buildTypeLower"/classes.jar "$output_dir/$output_name.jar"
  cp -rp app/.cxx/cmake/"$buildTypeLower"/arm64-v8a/output/dcg/include/ "$output_dir/include/"
  cp -rp app/.cxx/cmake/"$buildTypeLower"/arm64-v8a/output/dcg/"$buildType"/ "$output_dir/arm64-v8a/"
  cp -rp app/.cxx/cmake/"$buildTypeLower"/armeabi-v7a/output/dcg/"$buildType"/ "$output_dir/armeabi-v7a/"
  cp -rp app/.cxx/cmake/"$buildTypeLower"/x86/output/dcg/"$buildType"/ "$output_dir/x86/"
  cp -rp app/.cxx/cmake/"$buildTypeLower"/x86_64/output/dcg/"$buildType"/ "$output_dir/x86_64/"
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
