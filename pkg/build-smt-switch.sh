#!/bin/bash

# Usage: ./build-smt-switch <solver>

SOLVER=$1

cd smt-switch
./contrib/setup-$SOLVER.sh
./configure.sh --$SOLVER
cd build
make

cd ../../

mkdir lib
cp smt-switch/build/libsmt-switch.so ./lib
cp smt-switch/build/$SOLVER/libsmt-switch-$SOLVER.so ./lib

mkdir include
cp -r smt-switch/include ./include/smt-switch
