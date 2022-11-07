#!/usr/bin/env bash

set -e
set -x

ROOT_PATH=$(pwd)

grep "set(IRIS_PLUGIN_VERSION \".*\")" ${ROOT_PATH}/CMakeLists.txt | cut -d "\"" -f 2