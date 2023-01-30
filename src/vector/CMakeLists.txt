cmake_minimum_required(VERSION 3.11.0)
project(Vector VERSION 1.0.0)

add_executable(vector main.cpp)
target_link_libraries(vector GL GLEW GLU glut glfw)

target_clangformat_setup(vector)
