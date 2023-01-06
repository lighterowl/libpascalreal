#!/usr/bin/env bash

set -e

btype=$1
mkdir "build_${btype}_${CC}"
cd "build_${btype}_${CC}"
cmake -G Ninja .. "-DCMAKE_BUILD_TYPE=${btype}"
ninja -v

./libpascalreal_test

exit 0
