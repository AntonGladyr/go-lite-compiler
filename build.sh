#!/bin/bash

# Build the compiler
./buildMakefile.sh 
make -C ./build
cd build/bin
cp golite ../
cd ../..
