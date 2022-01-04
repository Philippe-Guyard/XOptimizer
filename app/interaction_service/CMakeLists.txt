cmake_minimum_required(VERSION 3.20)

project(interaction_service VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS QuickWidgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    testing.h
    testing.cpp
    mainwindow.h
    mainwindow.ui
    utils/api_wrapper.cpp
    utils/api_wrapper.moc
    utils/api_wrapper.h
    utils/order_parser.cpp
    interaction_service.cpp
    interaction_service.h
    utils/order_parser.h
    file_storage.cpp
    file_storage.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(interaction_service
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET interaction_service APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(interaction_service SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(interaction_service
            ${PROJECT_SOURCES} qml.qrc
        )
    endif()
endif()

target_link_libraries(interaction_service PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::QuickWidgets)

set_target_properties(interaction_service PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

set(PARSER_FILES
    parser/pbf-parser.cpp
    parser/pbf-parser.h
)

add_subdirectory(parser/)
target_link_libraries(interaction_service PRIVATE pbf_parser)

add_subdirectory(core-algo/)
# target_include_directories(interaction_service PUBLIC ${CORE_ALGO})
target_link_libraries(interaction_service PUBLIC CoreAlgo_Source)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(interaction_service)
endif()
