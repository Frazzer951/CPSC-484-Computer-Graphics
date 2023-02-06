cmake_minimum_required(VERSION 3.11.0)
project(Teapot VERSION 1.0.0)

add_executable(teapot opengl_with_rot_teapot.cpp)
target_link_libraries(teapot GL GLEW GLU glut glfw)

target_clangformat_setup(teapot)
