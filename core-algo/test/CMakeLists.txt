cmake_minimum_required(VERSION 3.10)                    # CMake version check
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

# Fetch newest stable version of GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)      # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES "*.cpp" "*.cc")
file(GLOB_RECURSE TEST_HEADERS "*.hpp")
add_library(Test ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(Test gtest_main)               # Google Test