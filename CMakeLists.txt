cmake_minimum_required(VERSION 3.20)

project(RenderCore)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(src/)
# add_subdirectory(examples/test/)
add_subdirectory(examples/inputExample/)
add_subdirectory(examples/materialsExample/)