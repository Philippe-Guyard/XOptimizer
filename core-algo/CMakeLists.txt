cmake_minimum_required(VERSION 3.14)                        # CMake version check

project(LogistiX_CoreAlgo                                   # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                                  # Enable C++14 standard. Note GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)                         # Enforce C++14 standard.        

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR                  # Enforce use of GNU Compiler for expected behaviours
    CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    option(TEST "Testing: " OFF)
    option(STABLE "Stable: " ON)

    if(NOT TEST)                                            # Without tests
        message("Testing is OFF")
        if(STABLE)                                          # From production code base
            message("Build from stable code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c"                                  # External librarbies source files
                "lib/**.cpp" 
                "src/**.cpp")                               # Stable source files
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h"                                  # External libraries header files
                "lib/**.hpp" 
                "src/**.hpp")                               # Stable header files
        else()                                              # From experiment code base
            message("Build from experiment code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c"                                  # External librarbies source files
                "lib/**.cpp" 
                "temp/**.cpp")                              # Experiment source files
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h"                                  # External libraries header files
                "lib/**.hpp" 
                "temp/**.hpp")                              # Experiment header files
        endif()

        list(REMOVE_ITEM                                    # Exclude example.cpp with main function in blossom v library.s
            SOURCES 
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/blossom5-v2_05/example.cpp)
        
        add_library(CoreAlgo_Source ${SOURCES} ${HEADERS})  # Source files
    else()                                                  # With tests
        message("Testing is ON")
        if(STABLE)                                          # From production code base
            message("Build from stable code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c"                                  # External libraries source files
                "lib/**.cpp" 
                "src/**.cpp"                                # Stable source files
                "test/src/**.cpp")                          # Test cases source files
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h"                                  # External libraries header files
                "lib/**.hpp" 
                "src/**.hpp"                                # Stable header files
                "test/src/**.hpp")                          # Test cases header files
            file(GLOB_RECURSE 
                TEST_SOURCES 
                "test/src/**.cc")                           # Test cases
        else()                                              # From experiment code base
            message("Build from experiment code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c"                                  # External libraries source files
                "lib/**.cpp" 
                "temp/**.cpp"                               # Experiments source files
                "test/temp/**.cpp")                         # Test cases source files
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h"                                  # External libraries header files
                "lib/**.hpp" 
                "temp/**.hpp"                               # experiment header files
                "test/temp/**.hpp")                         # Test cases header files
            file(GLOB_RECURSE 
                TEST_SOURCES 
                "test/temp/**.cc")                          # Test cases
        endif()
        
        list(REMOVE_ITEM                                    # Exclude example.cpp with main function in blossom v library.s
            SOURCES 
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/blossom5-v2_05/example.cpp)

        add_library(CoreAlgo_Source ${SOURCES} ${HEADERS})  # Source files

        # Fetch newest stable version of GoogleTest
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows: Prevent overriding the parent project's compiler/linker settings
        FetchContent_MakeAvailable(googletest)

        enable_testing()

        add_executable(Library ${TEST_SOURCES})             # Test files
        target_link_libraries(Library CoreAlgo_Source)      # Link to source files
        target_link_libraries(Library gtest_main)           # Google Test

        include(GoogleTest)
        gtest_discover_tests(Library)
    endif()

    unset(TEST CACHE)                                       # Reset cached variables
endif()