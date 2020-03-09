#!/bin/bash

# Build the compiler

make clean -C ./build
make -C ./build
cd build
rm -f golite
cd bin
cp golite ../
