cmake_minimum_required(VERSION 3.11.0)
project(OpenGl VERSION 1.0.0)

add_executable(opengl opengl.cpp)
target_link_libraries(opengl GL GLEW GLU glut glfw)
