cmake_minimum_required(VERSION 3.6)
project(compi1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        part_a.cpp
        part_b.cpp
        scanner.lex
        tokens.hpp)

add_executable(compi1 ${SOURCE_FILES})