cmake_minimum_required(VERSION 3.22)
project(fileIOs_wordPairs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fileIOs_wordPairs
        fileIOs_wordPairs.cpp
        fileIOs_wordPairs.h
        unitTests.h
        main.cpp)
