cmake_minimum_required(VERSION 3.5)

project(imageviewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

set(TS_FILES imageviewer_en_IN.ts)

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datahandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/datahandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h)
set(UI
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

add_subdirectory(Tools)

add_executable(imageviewer
    ${SOURCE}
    ${HEADERS}
    ${UI}
    ${TS_FILES}
    )

option(BUILD_TESTING "Enable tests" OFF)

target_link_libraries(imageviewer PRIVATE Qt5::Widgets)

# add the binary tree to the search path for include files
target_include_directories(imageviewer PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/Events"
    )

target_include_directories(imageviewer PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/Tools"
    )
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
