cmake_minimum_required(VERSION 3.5)

project(EagleEyeTests LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)
SET(QT_TEST_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(HDRS_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../Singletons/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/imagereadwriteutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/displayformatutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/imageprocessingutilities.h
)

set(SRCS_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../Singletons/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/imagereadwriteutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/displayformatutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/imageprocessingutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwriteutilitiestest.cpp
)


SET(EAGLEEYE_TEST_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}}
    ${CMAKE_CURRENT_SOURCE_DIR}}/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/Tests
)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EAGLEEYE_TEST_INCLUDE_PATH}
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestImages/TestImage.png
    ${CMAKE_CURRENT_BINARY_DIR}/TestImage.png COPYONLY)

enable_testing()


add_executable(EagleEyeTests
  ${SRCS_TEST}
  ${HDRS_TEST}
)


TARGET_LINK_LIBRARIES(EagleEyeTests
  ${QT_TEST_LIBRARIES}
  ${ITK_LIBRARIES}
)

ADD_TEST(NAME EagleEyeTests COMMAND EagleEyeTests)
