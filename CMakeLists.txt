cmake_minimum_required(VERSION 3.30)
project(cript)

set(CMAKE_CXX_STANDARD 23)

add_executable(cript main.cpp
        caesarCyph.cpp
        caesarCyph.h)
