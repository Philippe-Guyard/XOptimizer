cmake_minimum_required(VERSION 3.14)                    # CMake version check

project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)                     # Enforce C++14 standard.        
#set(CMAKE_CXX_FLAGS "/EHsc")                            # Enable /EH to build C++ code that follows the C++ standard for exception handling.

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")                # Enforce use of GNU Compiler for expected behaviours
    option(TEST "Testing: " OFF)

if(TEST)                                                # In case of testing
    message("Testing is ON")
    file(GLOB_RECURSE SOURCES "lib/**.c" "lib/**.cpp" "temp/**.cpp" "test/**.cpp" "temp/map.cpp")
    file(GLOB_RECURSE HEADERS "lib/**.h" "lib/**.hpp" "temp/**.hpp" "test/**.hpp" "temp/map.hpp")
else()                                                  #In case of releasing
    message("Testing is OFF")
    file(GLOB_RECURSE SOURCES "lib/**.c" "lib/**.cpp" "src/**.cpp" "temp/map.cpp")
    file(GLOB_RECURSE HEADERS "lib/**.h" "lib/**.hpp" "src/**.hpp" "temp/map.hpp")
endif()

list(REMOVE_ITEM                                        # Exclude example.cpp with main function in blossom v library.s
    SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/blossom5-v2_05/example.cpp)

add_library(Source ${SOURCES} ${HEADERS})               # Source files

# Fetch newest stable version of GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)      # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

if (TEST)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES "test/**.cc")
    add_executable(Library ${TEST_SOURCES})                 # Test files
    target_link_libraries(Library Source)                   # Link to source files
    target_link_libraries(Library gtest_main)               # Google Test

    include(GoogleTest)
    gtest_discover_tests(Library)
endif()

unset(TEST CACHE)                                             # Reset cached variables
