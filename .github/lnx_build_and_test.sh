#!/usr/bin/env bash

set -e

btype=$1
mkdir "build_${btype}_${CC}"
cd "build_${btype}_${CC}"
cmake .. "-DCMAKE_BUILD_TYPE=${btype}"
make -j2

./libpascalreal_test

exit 0
