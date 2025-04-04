#!/bin/bash
set -xe

CFLAGS="-Wall -Wextra -ggdb -Wswitch-enum"
LIBS="-lm -ldl -lpthread"
RAYLIB_PATH="./raylib/raylib-5.5_linux_amd64"

# Ensure the build directory exists
mkdir -p build

cc $CFLAGS -I"$RAYLIB_PATH/include" \
    main.c -o ./build/ranomart  \
    -L"$RAYLIB_PATH/lib" -lraylib \
    $LIBS

# Execute the compiled program
LD_LIBRARY_PATH=./raylib/raylib-5.5_linux_amd64/lib 
./build/ranomart gui
