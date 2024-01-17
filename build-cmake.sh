#!/bin/bash

if [ ! -d "build" ]; then 
    mkdir build
fi

cd build
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=../wb55.cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- -j 4