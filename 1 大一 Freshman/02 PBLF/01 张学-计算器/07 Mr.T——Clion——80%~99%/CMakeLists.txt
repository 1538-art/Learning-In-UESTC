cmake_minimum_required(VERSION 3.26)
project(Calculator_v2_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(Calculator_v2_0 main.c
        Stack.c
        Stack.h
        Calculator.c
        Calculator.h
        linked-list.c
        linked-list.h
        linked-list-stack.c
        linked-list-stack.h)
