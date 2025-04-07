#!/bin/bash
set -xe

CFLAGS="-Wall -Wextra -ggdb -Wswitch-enum"
LIBS="-lm -ldl -lpthread"
RAYLIB_PATH="./raylib/raylib-5.5_linux_amd64"

# Files
INPUT_FILE="src/randomart.c ./src/ffmpeg_linux.c"
OUTPUT_FILE="./build/ranomart"

# Ensure the build directory exists
mkdir -p build

cc $CFLAGS -I"$RAYLIB_PATH/include" \
    $INPUT_FILE -o $OUTPUT_FILE  \
    -L"$RAYLIB_PATH/lib" -lraylib \
    -Wl,-rpath,"$RAYLIB_PATH/lib" \
    $LIBS

# Execute the compiled program
./build/ranomart gui
