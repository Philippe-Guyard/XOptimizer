cmake_minimum_required(VERSION 3.20)
project(XOptimizer)

set(CMAKE_CXX_STANDARD 17)


if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(IS_64_BIT TRUE)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(IS_64_BIT FALSE)
else()
    message(FATAL_ERROR "Bad architecture")
endif()

set(PROTO_PATH "${CMAKE_CURRENT_LIST_DIR}/proto")
set(PROTOC_ZIP_PATH "${PROTO_PATH}/protoc.zip")
set(LIBPROTOBUF_ZIP_PATH "${PROTO_PATH}/protobuf.zip")
set(PROTOC_UNZIP_PATH "${PROTO_PATH}/protoc")
set(LIBPROTOBUF_UNZIP_PATH "${PROTO_PATH}/libprotobuf")
set(LIBPROTOBUF_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip")
if (WIN32 OR WIN64)
    set(PROTOC_FILENAME "protoc.exe")
    if (IS_64_BIT)
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protoc-3.19.1-win64.zip")
    else()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protoc-3.19.1-win32.zip")
    endif()
elseif (UNIX)
    set(PROTOC_FILENAME "protoc")
    if (APPLE)
        if (NOT IS_64_BIT)
            message(FATAL_ERROR "Not 64-bit macOS not supported")
        endif()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protoc-3.19.1-osx-x86_64.zip")
    elseif(IS_64_BIT)
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protoc-3.19.1-linux-x86_64.zip")
    else()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protoc-3.19.1-linux-x86_32.zip")
    endif()
else()
    message(FATAL_ERROR "Unknown OS")
endif()
set(PROTOC_PATH "${PROTOC_UNZIP_PATH}/bin/${PROTOC_FILENAME}")
set(PROTOC_INCLUDE_PATH "${PROTOC_UNZIP_PATH}/include")
message("${PROTOC_PATH}")

function(protoc_sanity_check OUTPUT)
    message("Verifying proto install...")
    if (NOT EXISTS ${PROTOC_PATH} OR NOT EXISTS ${PROTOC_INCLUDE_PATH} OR NOT EXISTS ${LIBPROTOBUF_UNZIP_PATH})
        set(RESULT FALSE)
    else()
        execute_process(COMMAND ${PROTOC_PATH} --version RESULT_VARIABLE PROTOC_RESULT OUTPUT_VARIABLE PROTOC_OUTPUT)
        if ((PROTOC_RESULT EQUAL 0) AND ("${PROTOC_OUTPUT}" STREQUAL "libprotoc 3.19.1\n"))
            set(RESULT TRUE)
        else()
            set(RESULT FALSE)
        endif()
    endif()
    if (RESULT)
        message("Success")
    else()
        message("Failure")
    endif()
    set(${OUTPUT} ${RESULT} PARENT_SCOPE)
endfunction()

protoc_sanity_check(PROTOC_SANITY_CHECK)

if (NOT PROTOC_SANITY_CHECK)
    if (EXISTS ${PROTO_PATH})
        message(WARNING "Bad installation of proto, attempting to reinstall...")
        file(REMOVE ${PROTO_PATH})
    endif()
    make_directory(${CMAKE_CURRENT_LIST_DIR}/generated)
    make_directory(${PROTO_PATH})
    message("Downloading ${PROTOC_URL}...")
    file(DOWNLOAD ${PROTOC_URL} ${PROTOC_ZIP_PATH})
    message("Installing protoc...")
    file(ARCHIVE_EXTRACT INPUT ${PROTOC_ZIP_PATH} DESTINATION ${PROTOC_UNZIP_PATH})
    file(REMOVE ${PROTOC_ZIP_PATH})
    message("Downloading ${LIBPROTOBUF_URL}...")
    file(DOWNLOAD ${LIBPROTOBUF_URL} ${LIBPROTOBUF_ZIP_PATH})
    message("Installing protoc lib...")
    file(ARCHIVE_EXTRACT INPUT ${LIBPROTOBUF_ZIP_PATH} DESTINATION ${LIBPROTOBUF_UNZIP_PATH})
    file(REMOVE ${LIBPROTOBUF_ZIP_PATH})
endif()

if (NOT PROTOC_SANITY_CHECK)
    protoc_sanity_check(PROTOC_SANITY_CHECK)

    if (NOT PROTOC_SANITY_CHECK)
        message(FATAL_ERROR "Failed to install protoc")
    endif()
endif()

set(LIBPROTOBUF_PATH "${LIBPROTOBUF_UNZIP_PATH}/protobuf-3.19.1")

# build protobuf
set(protobuf_source_dir ${LIBPROTOBUF_PATH})
set(protobuf_SHARED_OR_STATIC "SHARED")
set(protobuf_VERSION "3.19.1")
include("${LIBPROTOBUF_PATH}/cmake/libprotobuf-lite.cmake")
include("${LIBPROTOBUF_PATH}/cmake/libprotobuf.cmake")

set(GENERATED_PARSER_FILES
        "${CMAKE_CURRENT_LIST_DIR}/generated/fileformat.pb.h"
        "${CMAKE_CURRENT_LIST_DIR}/generated/fileformat.pb.cc"
        "${CMAKE_CURRENT_LIST_DIR}/generated/osmformat.pb.h"
        "${CMAKE_CURRENT_LIST_DIR}/generated/osmformat.pb.cc"
)
add_custom_command(
        OUTPUT ${GENERATED_PARSER_FILES}
        COMMAND ${PROTOC_PATH}
            "-I${CMAKE_CURRENT_LIST_DIR}/prototypes"
            "--cpp_out=${CMAKE_CURRENT_LIST_DIR}/generated"
            "${CMAKE_CURRENT_LIST_DIR}/prototypes/fileformat.proto"
            "${CMAKE_CURRENT_LIST_DIR}/prototypes/osmformat.proto"
)
set(PROTO_LIBRARIES
        "${PROTOC_UNZIP_PATH}/include"
        "${CMAKE_CURRENT_LIST_DIR}/generated"
        "${LIBPROTOBUF_PATH}/src"
)
add_library(pbf_parser_generated ${GENERATED_PARSER_FILES})
target_include_directories(pbf_parser_generated PUBLIC ${PROTO_LIBRARIES})
target_link_libraries(pbf_parser_generated protobuf::libprotobuf)
add_library(pbf_parser "${CMAKE_CURRENT_LIST_DIR}/pbf-parser.h" "${CMAKE_CURRENT_LIST_DIR}/pbf-parser.cpp")
target_include_directories(pbf_parser PUBLIC ${PROTO_LIBRARIES})
target_link_libraries(pbf_parser pbf_parser_generated)
