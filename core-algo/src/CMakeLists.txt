cmake_minimum_required(VERSION 3.10)                    # CMake version check
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

file(GLOB_RECURSE MAIN_SOURCES "*.cpp")
file(GLOB_RECURSE MAIN_HEADERS "*.hpp")
add_library(Source ${MAIN_SOURCES} ${MAIN_HEADERS})