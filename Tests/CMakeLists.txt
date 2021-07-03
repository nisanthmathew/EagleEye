cmake_minimum_required(VERSION 3.5)

project(EagleEyeTests LANGUAGES CXX)
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(HDRS_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tools/filereadwrite.h
)

set(SRCS_TEST
  ${CMAKE_CURRENT_SOURCE_DIR}/ToolsTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../Tools/filereadwrite.cpp
)


SET(EAGLEEYE_TEST_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}}/../Tools
)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EAGLEEYE_TEST_INCLUDE_PATH}
)

enable_testing()


add_executable(EagleEyeTests
  ${SRCS_TEST}
  ${HDRS_TEST}
)


TARGET_LINK_LIBRARIES(EagleEyeTests
  Qt5::Test
  Qt5::Gui
)

ADD_TEST(NAME EagleEyeTests COMMAND EagleEyeTests)