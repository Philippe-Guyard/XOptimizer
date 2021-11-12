cmake_minimum_required(VERSION 3.14)                    # CMake version check
project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

option(TEST "Testing: " OFF)

if(TEST)                                                # In case of testing
    add_subdirectory(test)

    enable_testing()

    file(GLOB_RECURSE TEMP_SOURCES "temp/*.cpp")
    file(GLOB_RECURSE TEMP_HEADERS "temp/*.hpp")
    add_library(TempLib ${TEMP_SOURCES} ${TEMP_HEADERS})# Temporary files
    target_link_libraries(TempLib Test)                 # Tests and test-aiding files
    
    include(GoogleTest)
    gtest_discover_tests(TempLib)
else()                                                  #In case of releasing
    add_subdirectory(src)
    target_link_libraries(CoreAlgoLib Source)           # Main source files
endif()

unset(TEST)                                             # Reset cached variables