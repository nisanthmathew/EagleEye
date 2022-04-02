cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LIBRARY_NAME ${PROJECT_NAME}_tools)

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwrite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/displayformat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/itkutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/eeroiqrubberband.cpp
)

SET(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwrite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/displayformat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/itkutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/eeroiqrubberband.h
)

add_library(${LIBRARY_NAME} STATIC
    ${SOURCE}
    ${HEADERS}
    )

target_link_libraries(${LIBRARY_NAME}
     ${QT_LIBRARIES}
     ${ITK_LIBRARIES}
    )
