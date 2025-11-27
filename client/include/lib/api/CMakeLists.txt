# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
add_library(
    API 
    STATIC
    httplib.h
    restapi.h
    ../../../src/lib/api/restapi.cpp
)

# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
target_include_directories(
    API 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    API 
    PROPERTIES
    AUTOMOC ON
)

target_link_libraries(API PUBLIC Qt6::Widgets)