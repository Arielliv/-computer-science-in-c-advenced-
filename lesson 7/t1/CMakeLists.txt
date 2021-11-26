cmake_minimum_required(VERSION 3.17)
project(t1 C)

set(CMAKE_C_STANDARD 99)

add_executable(t1 "Source Files/main.c" "Header Files/trees.h" "Source Files/trees.c")