cmake_minimum_required(VERSION 3.14)

project(interaction_service_qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

set (sources
    main.cpp
    interaction_service_qt.cpp
    utils/downloader.cpp
    utils/geocoder.cpp
    utils/order_parser.cpp
)

set(headers
    interaction_service_qt.h
)

add_executable(interaction_service_qt
    main.cpp
    interaction_service_qt.cpp
    interaction_service_qt.h
    utils/downloader.cpp
    utils/geocoder.cpp
    utils/order_parser.cpp
)
add_subdirectory(parser)


target_link_libraries(interaction_service_qt Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
