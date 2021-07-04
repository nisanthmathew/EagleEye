cmake_minimum_required(VERSION 3.5)

set (PROJECT_NAME EagleEyeViewer)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
SET(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)

add_subdirectory(Tools)

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

add_executable(${PROJECT_NAME}
    ${SOURCE}
    ${HEADERS}
    ${UI}
    )

option(BUILD_TESTING "Enable tests" ON)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${QT_LIBRARIES}
    ${PROJECT_NAME}_tools
    )

# add the binary tree to the search path for include files
target_include_directories(${PROJECT_NAME} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}"
                          "${PROJECT_SOURCE_DIR}/Tools"
                          )
IF (BUILD_TESTING)
  add_subdirectory(Tests)
ENDIF()
