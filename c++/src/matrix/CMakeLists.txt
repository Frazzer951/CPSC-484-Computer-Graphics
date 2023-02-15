cmake_minimum_required(VERSION 3.11.0)
project(Matrix VERSION 1.0.0)

add_executable(matrix main.cpp vector3dT.h matrix3dT.h)

target_clangformat_setup(matrix)
