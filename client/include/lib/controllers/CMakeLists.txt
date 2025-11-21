# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
add_library(
    CONTROLLER 
    STATIC
    ApplicationController.h
    ../../../src/lib/controllers/ApplicationController.cpp
)

# ============================================
# CREATE LIBRARY TO INCLUDE ALL .h FILES
# ============================================
target_include_directories(
    CONTROLLER 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    CONTROLLER 
    PROPERTIES
    AUTOMOC ON
)

target_link_libraries(CONTROLLER PUBLIC Qt6::Widgets)



