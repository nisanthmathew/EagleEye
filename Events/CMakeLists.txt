cmake_minimum_required(VERSION 3.5)

project(imageviewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/imageviewerevents.cpp
    PARENT_SCPOE
    )

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/imageviewerevents.h
    PARENT_SCPOE
    )
