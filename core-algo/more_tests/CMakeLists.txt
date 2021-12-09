cmake_minimum_required(VERSION 3.14)                    # CMake version check
project(LogistiX_CoreAlgo                               # Set the project name
        VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)                              # Enable C++14 standard. Note GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)                     # Enforce C++14 standard.        

option(TEST "Testing: " ON)

if(TEST)                                                # In case of testing
    message("Testing is ON")
    file(GLOB_RECURSE SOURCES "src/**.cpp" "temp/*.cpp")
    file(GLOB_RECURSE HEADERS "src/**.hpp" "temp/*.hpp")
else()                                                  #In case of releasing
    message("Testing is OFF")
    file(GLOB_RECURSE SOURCES "lib/**.c" "lib/**.cpp" "src/**.cpp" "test/**.cpp")
    file(GLOB_RECURSE HEADERS "lib/**.h" "lib/**.hpp" "src/**.hpp" "test/**.hpp")
endif()

list(REMOVE_ITEM                                        # Exclude example.cpp with main function in blossom v library.s
    SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/blossom5-v2_05/example.cpp)

list(REMOVE_ITEM                                        
    SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/temp/matching.cpp)

list(REMOVE_ITEM
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/temp/graph_matching.cpp)

list(REMOVE_ITEM
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/temp/graph_TSP_approximation.cpp)

list(REMOVE_ITEM
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/temp/TSP_approximation.cpp})

add_library(Source ${SOURCES} ${HEADERS})                # Source files
add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/temp/test.cpp)         # Test files
target_link_libraries(test Source)    

unset(TEST CACHE)                                             # Reset cached variables