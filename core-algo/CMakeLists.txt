cmake_minimum_required(VERSION 3.10)                    # CMake version check
project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11

# Fetch newest stable version of GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)      # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

# Build a library from files to be tested
file(GLOB TEMP_SOURCES temp/*.cpp)
file(GLOB TEMP_HEADERS temp/*.hxx)
add_library(TempLib ${TEMP_SOURCES} ${TEMP_HEADERS})

# Build executables
# If necessary, use the RELATIVE flag, otherwise each source file may be listed 
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
# file( GLOB APP_SOURCES RELATIVE app/*.cxx )
file(GLOB APP_SOURCES app/*.cxx)
foreach(testsourcefile ${APP_SOURCES})
    add_executable(TempLib ${testsourcefile})
endforeach(testsourcefile ${APP_SOURCES})
enable_testing()
target_link_libraries(
    TempLib
    gtest_main
)
include(GoogleTest)
gtest_discover_tests(TempLib)
