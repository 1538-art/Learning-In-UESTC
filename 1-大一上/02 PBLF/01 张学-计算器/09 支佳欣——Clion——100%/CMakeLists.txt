cmake_minimum_required(VERSION 3.26)
project(Calculator C)

set(CMAKE_C_STANDARD 11)

add_executable(Calculator main.c
        Stack.c
        Calculate.c
        Stack.h
        Calculate.h)
