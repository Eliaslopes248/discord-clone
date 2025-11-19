# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
add_library(UI 
    STATIC
    MainWindow.h
    ../../../src/lib/MainWindow.cpp
)

# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
target_include_directories(
    UI 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    UI PROPERTIES
    AUTOMOC ON
)

target_link_libraries(UI PUBLIC Qt6::Widgets)



