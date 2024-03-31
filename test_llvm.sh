#!/bin/bash

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=linux.llvm.toolchain.cmake ..
make
ctest -V
