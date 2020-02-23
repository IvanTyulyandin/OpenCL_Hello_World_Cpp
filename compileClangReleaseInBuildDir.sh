#!/bin/bash

mkdir -p build
cp *.cl build/
cd build
cmake -DCMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ..
make -j 3
cd ..