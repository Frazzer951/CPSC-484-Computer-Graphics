cmake_minimum_required(VERSION 3.11.0)
project(CPCS_484_Computer_Graphics VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src/data_structs)
add_subdirectory(src/opengl)
add_subdirectory(src/teapot)
