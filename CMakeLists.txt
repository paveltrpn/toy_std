cmake_minimum_required(VERSION 3.0)

project (toy_containers)

set(CMAKE_CXX_COMPILER g++-13.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall \
                                        -Wextra \
                                        -Wpedantic \
                                        -Wno-unused-parameter \
                                        --std=c++2b")

set(LIBS -lm)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})
