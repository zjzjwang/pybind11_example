cmake_minimum_required(VERSION 3.18)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(pybind11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/pybind11)
include_directories(include external/pybind11/include)

add_subdirectory(src)
