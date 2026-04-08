cmake_minimum_required(VERSION 3.20)
project(trees)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(trees
        src/Treap.cpp
)

target_include_directories(trees PRIVATE include)

target_compile_options(trees PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
