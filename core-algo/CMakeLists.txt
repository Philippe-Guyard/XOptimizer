cmake_minimum_required(VERSION 3.14)                    # CMake version check
project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

option(TEST "Testing: " OFF)

if(TEST)                                                # In case of testing
    file(GLOB_RECURSE SOURCES "temp/*.cpp" "test/*.cpp")
    file(GLOB_RECURSE HEADERS "temp/*.hpp" "test/*.hpp")
else()                                                  #In case of releasing
    file(GLOB_RECURSE SOURCES "src/*.cpp" "test/*.cpp")
    file(GLOB_RECURSE HEADERS "src/*.hpp" "test/*.hpp")
endif()

add_library(Source ${SOURCES} ${HEADERS})               # Source files

# Fetch newest stable version of GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)      # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES "test/*.cc")
add_executable(Library ${TEST_SOURCES})                 # Test files
target_link_libraries(Library Source)                   # Link to source files
target_link_libraries(Library gtest_main)               # Google Test

include(GoogleTest)
gtest_discover_tests(Library)

unset(TEST)                                             # Reset cached variables