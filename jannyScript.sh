#!/bin/sh

# format src 
clang-format -style='google' -i src/*.cpp src/*.h
