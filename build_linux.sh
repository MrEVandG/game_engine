#!/usr/bin/bash

exec_loc=./build/game_engine
exec_debug_loc=./debug/game_engine

if ! [ -d ./build/ ]; then
    mkdir build
    cmake -DCMAKE_BUILD_TYPE=Release ..
fi

if ! [ -d ./debug/ ]; then
    mkdir debug
    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi

echo building...
# build using either debug mode or release mode
if [ $1 = "-d" ]; then
    echo build as debug...
    cmake -S . -B debug -DCMAKE_BUILD_TYPE=Debug
    cmake --build debug
    cp $exec_debug_loc .
else
    echo build as release...
    cmake -S . -B build
    cmake --build build
    cp $exec_loc .
fi