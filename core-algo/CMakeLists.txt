cmake_minimum_required(VERSION 3.14)                    # CMake version check
project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

option(TEST "Testing: " OFF)

add_subdirectory(test)
enable_testing()

if(TEST)                                                # In case of testing
    file(GLOB_RECURSE SOURCES "temp/*.cpp")
    file(GLOB_RECURSE HEADERS "temp/*.hpp")
else()                                                  #In case of releasing
    file(GLOB_RECURSE SOURCES "src/*.cpp")
    file(GLOB_RECURSE HEADERS "src/*.hpp")
endif()

add_library(Library ${SOURCES} ${HEADERS})              # Temporary files
target_link_libraries(Library Test)                     # Tests and test-aiding files

include(GoogleTest)
gtest_discover_tests(Library)

unset(TEST)                                             # Reset cached variables