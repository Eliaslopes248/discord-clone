# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
add_library(
    PAGES 
    STATIC
)

# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
target_include_directories(
    PAGES 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    PAGES PROPERTIES
    AUTOMOC ON
)

target_link_libraries(PAGES PUBLIC Qt6::Widgets)