SET(LIBRARY_NAME ${PROJECT_NAME}_utilities)

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwriteutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/displayformatutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/itkutilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingutilities.cpp
)

SET(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/imagereadwriteutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/displayformatutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/itkutilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingutilities.h
)

add_library(${LIBRARY_NAME} STATIC
    ${SOURCE}
    ${HEADERS}
    )

target_link_libraries(${LIBRARY_NAME}
     ${QT_LIBRARIES}
     ${ITK_LIBRARIES}
     ${PROJECT_NAME}_singletons
    )
