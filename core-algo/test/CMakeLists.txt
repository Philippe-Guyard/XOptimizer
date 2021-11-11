cmake_minimum_required(VERSION 3.10)                    # CMake version check
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

file(GLOB_RECURSE TEST_SOURCES "*.cpp" "*.cc")
file(GLOB_RECURSE TEST_HEADERS "*.hpp")
add_library(Test ${TEST_SOURCES} ${TEST_HEADERS})