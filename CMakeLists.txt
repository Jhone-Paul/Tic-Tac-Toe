cmake_minimum_required(VERSION 3.30)
project(game)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory("C:/Users/johnl/Desktop/glfw-3.4" ${CMAKE_BINARY_DIR}/glfw-build)
# Include GLAD
include_directories(${CMAKE_SOURCE_DIR}/glad/include)
add_library(glad STATIC glad/src/glad.c)

add_executable(game main.cpp)
target_link_libraries(game PRIVATE glad glfw)
