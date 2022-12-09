cmake_minimum_required(VERSION 3.13)

project(task2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE)

set(CMAKE_CXX_FLAGS "-DGLFW_INCLUDE_NONE -g -O0 -fsanitize=address")
add_subdirectory(../third_party third_party)

set(TASK2_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task2)

add_subdirectory(src)

target_link_libraries(task2
  PUBLIC
    assimp
    glad
    glfw
    glm
    stb_image
  )