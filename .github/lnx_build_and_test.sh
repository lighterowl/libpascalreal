#!/usr/bin/env bash

set -e

btype=$1
mkdir "build_${btype}_${CXX}"
cd "build_${btype}_${CXX}"
cmake .. "-DCMAKE_BUILD_TYPE=${btype}"
make -j2

./libpascalreal_test

exit 0
