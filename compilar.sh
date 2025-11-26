#!/bin/bash
# Script simple de compilación

mkdir -p build
cd build
cmake .. -G "Ninja"
ninja
