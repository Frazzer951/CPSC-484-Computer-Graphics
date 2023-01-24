cmake_minimum_required(VERSION 3.11.0)
project(CPCS_484_Computer_Graphics VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat)

add_subdirectory(src/opengl)

file(GLOB_RECURSE src_files
    "src/*.cpp"
    "src/*.c"
)

add_custom_target(clangtidy
    COMMAND
        clang-tidy
        -p ./build
        --fix-notes
        --fix-errors
        ${src_files}
    WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
    COMMENT
        "Running Clang Tidy..."
)
