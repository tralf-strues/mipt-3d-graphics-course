cmake_minimum_required(VERSION 3.13)

project(task1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -DGLFW_INCLUDE_NONE -g -O2 -fsanitize=address")

set(TASK1_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task1)

add_subdirectory(src)
add_subdirectory(../third_party third_party)

target_link_libraries(task1
  PUBLIC
    glad
    glfw
    glm
  )