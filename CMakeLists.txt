cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (toy_containers)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_compile_options(-g -Wall -Wextra -Wpedantic -std=c++20 -stdlib=libc++ -Wno-unused-parameter)
add_link_options(-stdlib=libc++)

set(SOURCES src/main.cpp src/raw_vector.h src/vector.h src/array.h src/stack.h)

add_executable(main ${SOURCES})
