#!/bin/bash

set -ex

ROOT_PATH=$(pwd)

grep "set(PLUGIN_VERSION \".*\")" ${ROOT_PATH}/CMakeLists.txt | cut -d "\"" -f 2
