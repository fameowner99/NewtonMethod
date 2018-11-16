cmake_minimum_required(VERSION 3.12)
project(numericalMethods)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(numericalMethods
        Matrix.cpp
        Matrix.hpp
        lab3.cpp)
