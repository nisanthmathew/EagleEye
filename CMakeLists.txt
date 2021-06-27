cmake_minimum_required(VERSION 3.5)

project(EagleEyeViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

set(TS_FILES imageviewer_en_IN.ts)

# add the binary tree to the search path for include files
include_directories(EagleEyeViewer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Tools"
    "${CMAKE_CURRENT_BINARY_DIR}/Tools"
    )

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datahandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/filereadwrite.cpp)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/datahandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/filereadwrite.h)

set(UI
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

add_executable(EagleEyeViewer
    ${SOURCE}
    ${HEADERS}
    ${UI}
    ${TS_FILES}
    )

option(BUILD_TESTING "Enable tests" ON)

target_link_libraries(EagleEyeViewer
    Qt5::Widgets
    Qt5::Gui
    )

IF (BUILD_TESTING)
  add_subdirectory(Tests)
ENDIF()

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
