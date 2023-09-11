cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (toy_containers)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall \
                                        -Wextra \
                                        -Wpedantic \
                                        -Wno-unused-parameter \
                                        --std=c++2b \
                                        --stdlib=libc++")

set(LIBS -lm)

set(SOURCES src/main.cpp src/common.h src/raw_vector.h src/vector.h)

add_executable(main ${SOURCES})
