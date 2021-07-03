cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LIBRARY_NAME ${PROJECT_NAME}_tools)

SET(${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/filereadwrite.h
    PARENT_SCOPE
)

set(${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/filereadwrite.cpp
    PARENT_SCOPE
)

add_library(${LIBRARY_NAME} SHARED
    filereadwrite.cpp
    filereadwrite.h)

target_link_libraries(${LIBRARY_NAME}
    ${QT_LIBRARIES})
