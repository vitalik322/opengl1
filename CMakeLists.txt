cmake_minimum_required(VERSION 3.11)
project(opengl1)

#
# External projects
#
include(FetchContent)

# GLFW
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

#
# Main project
#
 
add_executable(opengl1 src/main.cpp)
target_link_libraries(opengl1 glfw)
