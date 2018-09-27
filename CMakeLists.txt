cmake_minimum_required(VERSION 3.11)
project(opengl1)

#
# External projects
#
include(FetchContent)

# GLFW
message(STATUS "Fetching glfw")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        15cad0223543745d13d4ce2de040d3b7defb3870
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# GLAD
message(STATUS "Fetching glad")
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        4d3367c063fc23eea6fb5b7c91eb7bfd74a3599b
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

#
# Main project
#

set(SIMPLE_VERTEX_SHADER "${PROJECT_SOURCE_DIR}/shaders/simple.vs")
set(SIMPLE_FRAGMENT_SHADER "${PROJECT_SOURCE_DIR}/shaders/simple.fs")
configure_file(src/definitions.h.in src/definitions.h @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")

set(CMAKE_BUILD_TYPE Debug)

add_executable(opengl1 src/main.cpp)
target_link_libraries(opengl1 glfw)
target_link_libraries(opengl1 glad)
