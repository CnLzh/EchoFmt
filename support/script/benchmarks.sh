#!/bin/bash

cd ../../
mkdir -p build
cd build
cmake -DECHOFMT_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../support/cmake/linux.llvm.toolchain.cmake ..
make
