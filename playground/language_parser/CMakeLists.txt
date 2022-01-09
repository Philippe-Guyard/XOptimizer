cmake_minimum_required(VERSION 3.20)
project(xoptimizer_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(xoptimizer_parser main.cpp parser.cpp parser.h assumptions.cpp assumptions.h utils.h utils.cpp)
