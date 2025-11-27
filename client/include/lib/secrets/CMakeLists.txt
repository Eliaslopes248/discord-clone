# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
add_library(
    SECRETS 
    STATIC
    secrets.h
    secrets.cpp
)

# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
target_include_directories(
    SECRETS
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    SECRETS 
    PROPERTIES
    AUTOMOC ON
)

target_link_libraries( SECRETS PUBLIC Qt6::Widgets)