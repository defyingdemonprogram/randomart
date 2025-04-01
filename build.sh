#!/bin/bash
set -xe

CFLAGS="-Wall -Wextra -ggdb"

mkdir -p build
gcc $CFLAGS -o ./build/main main.c -lm

# Execute the executable
./build/main
