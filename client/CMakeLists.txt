cmake_minimum_required(VERSION 4.0)
# =====================================
# SET PROJECT NAME
# =====================================
project(app)

set(CMAKE_CXX_STANDARD 17)
# =====================================
# FIND REQUIRED PACKAGES FOR QT
# =====================================
set(CMAKE_PREFIX_PATH "~/Qt/6.10.0/macos" ${CMAKE_PREFIX_PATH})
find_package( Qt6 REQUIRED COMPONENTS Widgets REQUIRED)

# =====================================
# CREATE EXE TARGET
# =====================================
add_executable(${PROJECT_NAME} src/main.cpp)

# =====================================
# SUBDIRECTORIES
# =====================================
add_subdirectory(include/lib/ui)
add_subdirectory(include/lib/pages)
add_subdirectory(include/lib/controllers)


# =====================================
# LINK LIBRARIES
# =====================================
target_link_libraries(app PRIVATE Qt6::Widgets)
target_link_libraries(app PRIVATE UI)
target_link_libraries(app PRIVATE CONTROLLER)
target_link_libraries(app PRIVATE PAGES)
