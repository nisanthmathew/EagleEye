project(EagleEyeTests LANGUAGES CXX)
find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)
SET(QT_TEST_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test)

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
)


SET(EAGLEEYE_TEST_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/Tests
)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EAGLEEYE_TEST_INCLUDE_PATH}
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestImages/TestImage.png
    ${CMAKE_CURRENT_BINARY_DIR}/TestImage.png COPYONLY)

enable_testing()


set(SRCS_IMAGEREADWRITE_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwriteutilitiestest.cpp
)

add_executable(ImageReadWriteTest
  ${SRCS_TEST}
  ${HDRS_TEST}
  ${SRCS_IMAGEREADWRITE_TEST}
)


TARGET_LINK_LIBRARIES(ImageReadWriteTest
  ${QT_TEST_LIBRARIES}
  ${ITK_LIBRARIES}
)

ADD_TEST(NAME ImageReadWriteTest COMMAND ImageReadWriteTest)

set(SRCS_LOGGER_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/loggertest.cpp
)
add_executable(LoggerTest
  ${SRCS_TEST}
  ${HDRS_TEST}
  ${SRCS_LOGGER_TEST}
)


TARGET_LINK_LIBRARIES(LoggerTest
  ${QT_TEST_LIBRARIES}
  ${ITK_LIBRARIES}
)

ADD_TEST(NAME LoggerTest COMMAND LoggerTest)
