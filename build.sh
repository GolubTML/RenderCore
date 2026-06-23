#!/bin/bash

cmake -B build -DCMAKE_BUILD_TYPE=Debug

echo "Start compiling library.."
cmake --build build