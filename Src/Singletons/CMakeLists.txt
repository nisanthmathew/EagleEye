SET(LIBRARY_NAME ${PROJECT_NAME}_singletons)

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imagemodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageviewcontroller.cpp
)

SET(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imagemodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imageviewcontroller.h
)

add_library(${LIBRARY_NAME} STATIC
    ${SOURCE}
    ${HEADERS}
    )

target_link_libraries(${LIBRARY_NAME}
     ${QT_LIBRARIES}
     ${ITK_LIBRARIES}
    )
