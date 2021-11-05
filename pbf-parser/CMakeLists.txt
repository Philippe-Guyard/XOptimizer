cmake_minimum_required(VERSION 3.20)
project(XOptimizer)

set(CMAKE_CXX_STANDARD 17)

function(protoc_sanity_check PATH OUTPUT)
    if (NOT EXISTS "${PATH}/bin/${PROTOC_FILENAME}" OR NOT EXISTS "${PATH}/include")
        set(RESULT FALSE)
    else()
        execute_process(COMMAND
                "${PATH}/bin/${PROTOC_FILENAME}" --version
                RESULT_VARIABLE PROTOC_RESULT
                OUTPUT_VARIABLE PROTOC_OUTPUT)
        if ((PROTOC_RESULT EQUAL 0) AND ("${PROTOC_OUTPUT}" STREQUAL "libprotoc ${PROTO_VERSION}\n"))
            set(RESULT TRUE)
        else()
            set(RESULT FALSE)
        endif()
    endif()
    set(${OUTPUT} ${RESULT} PARENT_SCOPE)
endfunction()

function(check_install_library NAME URL SANITY_CHECK_FN INSTALL_FN INSTALL_PATH)
    set(PATH "${CMAKE_BINARY_DIR}/libs/${NAME}")
    message("Check ${NAME} installed...")
    if (SANITY_CHECK_FN)
        cmake_language(CALL ${SANITY_CHECK_FN} "${PATH}/${NAME}" SANITY_OUTPUT)
    elseif (EXISTS "${PATH}/${NAME}")
        set(SANITY_OUTPUT TRUE)
    else()
        set(SANITY_OUTPUT FALSE)
    endif()

    if (NOT SANITY_OUTPUT)
        message("${NAME} not found or malformed")
        file(MAKE_DIRECTORY "${PATH}/${NAME}")
        message("Downloading ${URL}...")
        file(DOWNLOAD ${URL} "${PATH}/${NAME}.zip")
        message("Installing ${NAME}...")
        file(ARCHIVE_EXTRACT INPUT "${PATH}/${NAME}.zip" DESTINATION "${PATH}/${NAME}")
        if (INSTALL_FN)
            cmake_language(CALL ${INSTALL_FN} "${PATH}/${NAME}")
        endif()
        file(REMOVE "${PATH}/${NAME}.zip")
        message("Check ${NAME} installed...")
        if (SANITY_CHECK_FN)
            cmake_language(CALL ${SANITY_CHECK_FN} "${PATH}/${NAME}" SANITY_OUTPUT)
        elseif (EXISTS "${PATH}/${NAME}")
            set(SANITY_OUTPUT TRUE)
        else()
            set(SANITY_OUTPUT FALSE)
        endif()
        if (NOT SANITY_OUTPUT)
            message(FATAL_ERROR "Failed to install ${NAME}")
        endif()
    endif()
    set(${INSTALL_PATH} "${PATH}/${NAME}" PARENT_SCOPE)
endfunction()

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(IS_64_BIT TRUE)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(IS_64_BIT FALSE)
else()
    message(FATAL_ERROR "Bad architecture")
endif()

set(PROTO_VERSION "3.19.1")
set(ZLIB_VERSION "1.2.11")
if (WIN32 OR WIN64)
    set(PROTOC_FILENAME "protoc.exe")
    if (IS_64_BIT)
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protoc-${PROTO_VERSION}-win64.zip")
    else()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protoc-${PROTO_VERSION}-win32.zip")
    endif()
elseif (UNIX)
    set(PROTOC_FILENAME "protoc")
    if (APPLE)
        if (NOT IS_64_BIT)
            message(FATAL_ERROR "Not 64-bit macOS not supported")
        endif()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protoc-${PROTO_VERSION}-osx-x86_64.zip")
    elseif(IS_64_BIT)
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protoc-${PROTO_VERSION}-linux-x86_64.zip")
    else()
        set(PROTOC_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protoc-${PROTO_VERSION}-linux-x86_32.zip")
    endif()
else()
    message(FATAL_ERROR "Unknown OS")
endif()

set(PROTO_PATH "${CMAKE_CURRENT_LIST_DIR}/proto")
set(LIBPROTOBUF_URL "https://github.com/protocolbuffers/protobuf/releases/download/v${PROTO_VERSION}/protobuf-cpp-${PROTO_VERSION}.zip")
set(ZLIB_URL https://github.com/madler/zlib/archive/refs/tags/v${ZLIB_VERSION}.zip)

check_install_library(protoc ${PROTOC_URL} protoc_sanity_check FALSE PROTOC_INSTALL_PATH)
check_install_library(libprotobuf ${LIBPROTOBUF_URL} FALSE FALSE LIBPROTOBUF_INSTALL_PATH)
check_install_library(zlib ${ZLIB_URL} FALSE FALSE ZLIB_INSTALL_PATH)

set(LIBPROTOBUF_PATH "${LIBPROTOBUF_INSTALL_PATH}/protobuf-3.19.1")
set(ZLIB_PATH "${ZLIB_INSTALL_PATH}/zlib-${ZLIB_VERSION}")

# build protobuf
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_CONFORMANCE OFF)
set(protobuf_BUILD_EXAMPLES OFF)
set(protobuf_BUILD_PROTOC_BINARIES OFF)
set(protobuf_BUILD_LIBPROTOC ON)
set(protobuf_BUILD_SHARED_LIBS FALSE)
add_subdirectory("${LIBPROTOBUF_PATH}/cmake")

add_subdirectory("${ZLIB_PATH}")

set(GENERATED_PARSER_FILES
        "${CMAKE_CURRENT_LIST_DIR}/generated/fileformat.pb.h"
        "${CMAKE_CURRENT_LIST_DIR}/generated/fileformat.pb.cc"
        "${CMAKE_CURRENT_LIST_DIR}/generated/osmformat.pb.h"
        "${CMAKE_CURRENT_LIST_DIR}/generated/osmformat.pb.cc"
)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/generated")
add_custom_command(
        OUTPUT ${GENERATED_PARSER_FILES}
        COMMAND "${PROTOC_INSTALL_PATH}/bin/${PROTOC_FILENAME}"
            "-I${CMAKE_CURRENT_LIST_DIR}/prototypes"
            "--cpp_out=${CMAKE_CURRENT_LIST_DIR}/generated"
            "${CMAKE_CURRENT_LIST_DIR}/prototypes/fileformat.proto"
            "${CMAKE_CURRENT_LIST_DIR}/prototypes/osmformat.proto"
)
set(PROTO_LIBRARIES
        "${CMAKE_CURRENT_LIST_DIR}/generated"
        "${LIBPROTOBUF_PATH}/src"
)
add_library(pbf_parser_generated ${GENERATED_PARSER_FILES})
target_include_directories(pbf_parser_generated PUBLIC ${PROTO_LIBRARIES})
target_link_libraries(pbf_parser_generated libprotobuf)
add_library(pbf_parser "${CMAKE_CURRENT_LIST_DIR}/pbf-parser.h" "${CMAKE_CURRENT_LIST_DIR}/pbf-parser.cpp")
target_include_directories(pbf_parser PUBLIC ${PROTO_LIBRARIES} "${ZLIB_PATH}")
target_link_libraries(pbf_parser pbf_parser_generated zlibstatic)
