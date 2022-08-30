SET(LIBRARY_NAME ${PROJECT_NAME}_menuitems)

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/filemenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsmenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingmenu.cpp
)

SET(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/filemenu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsmenu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imageprocessingmenu.h
)

add_library(${LIBRARY_NAME} STATIC
    ${SOURCE}
    ${HEADERS}
    )

target_link_libraries(${LIBRARY_NAME}
     ${QT_LIBRARIES}
     ${ITK_LIBRARIES}
     ${PROJECT_NAME}_utilities
    )
