cmake_minimum_required(VERSION 3.14)                    # CMake version check

project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)                     # Enforce C++14 standard.        

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR              # Enforce use of GNU Compiler for expected behaviours
    CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    option(TEST "Testing: " OFF)
    option(STABLE "Stable: " ON)

    if(NOT TEST)
        message("Testing is OFF")
        if(STABLE)
            message("Build from stable code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c" 
                "lib/**.cpp" 
                "src/**.cpp")
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h" 
                "lib/**.hpp" 
                "src/**.hpp")
        else()
            message("Build from experiment code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c" 
                "lib/**.cpp" 
                "temp/**.cpp")
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h" 
                "lib/**.hpp" 
                "temp/**.hpp")
        endif()

        list(REMOVE_ITEM                                    # Exclude example.cpp with main function in blossom v library.s
            SOURCES 
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/blossom5-v2_05/example.cpp)
        
        add_library(CoreAlgo_Source ${SOURCES} ${HEADERS})  # Source files
    else()
        message("Testing is ON")
        if(STABLE)
            message("Build from stable code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c" 
                "lib/**.cpp" 
                "src/**.cpp" 
                "test/src/**.cpp")
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h" 
                "lib/**.hpp" 
                "src/**.hpp" 
                "test/src/**.hpp")
            file(GLOB_RECURSE 
                TEST_SOURCES 
                "test/src/**.cc")
        else()
            message("Build from experiment code base")
            file(GLOB_RECURSE 
                SOURCES 
                "lib/**.c" 
                "lib/**.cpp" 
                "temp/**.cpp" 
                "test/temp/**.cpp")
            file(GLOB_RECURSE 
                HEADERS 
                "lib/**.h" 
                "lib/**.hpp" 
                "temp/**.hpp" 
                "test/temp/**.hpp")
            file(GLOB_RECURSE 
                TEST_SOURCES 
                "test/temp/**.cc")
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

    unset(TEST CACHE)                                   # Reset cached variables
endif()