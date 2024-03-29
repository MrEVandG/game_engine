#!/usr/bin/bash

exec_loc=./build/game_engine

if ! [ -d ./build/ ]; then
    mkdir build
fi

if ! [ -f ./build/CMakeCache.txt ]; then
    cmake -S . -B ./build
fi

echo building...
cmake --build build

# just makes things easier for me
cp $exec_loc .