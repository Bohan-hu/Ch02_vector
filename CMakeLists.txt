cmake_minimum_required(VERSION 3.8)
project(Ch02_vector)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp myvector.cpp myvector.h)
add_executable(Ch02_vector ${SOURCE_FILES})