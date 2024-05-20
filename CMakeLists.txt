cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (toy_std)

add_compile_options(-g 
                    -Wall 
                    -Wextra 
                    -Wpedantic 
                    #-stdlib=libc++ 
                    -Wno-unused-parameter)

#add_link_options(-stdlib=libc++)

option(WITH_UBSAN "build with undefined behavior sanitizer" OFF)
option(WITH_ASAN  "build with address sanitizer" OFF)
option(WITH_TSAN  "build with thread sanitizer" OFF)
option(WITH_MSAN  "build with memory sanitizer" OFF)

if(WITH_UBSAN)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

if(WITH_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

if(WITH_TSAN)
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
endif()

if(WITH_MSAN)
  add_compile_options(-fsanitize=memory)
  add_link_options(-fsanitize=memory)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_SCAN_FOR_MODULES)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(SRC_DIR "src")
set(TST_DIR "test")
set(WORK_DIR "/mnt/main_disk/code")

# find globally installed system package
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# find local hand-build package
# set(BOOST_LOCAL "${WORK_DIR}/extern_libs/boost_1_84_0-clang")
# 
# set(ENV{LD_LIBRARY_PATH} ${LD_LIBRARY_PATH}:${BOOST_LOCAL}/lib)
# include_directories (${BOOST_LOCAL})
# link_directories(${BOOST_LOCAL}/lib)

include_directories (${SRC_DIR})

add_library(toy_std)
target_sources(toy_std
  PUBLIC
    FILE_SET CXX_MODULES FILES
    ${SRC_DIR}/concepts.cpp
    ${SRC_DIR}/array.cpp
    ${SRC_DIR}/raw_list.cpp
    ${SRC_DIR}/stack.cpp
    ${SRC_DIR}/vector.cpp
    ${SRC_DIR}/raw_vector.cpp
    ${SRC_DIR}/iterator_traits.cpp
    ${SRC_DIR}/toy_std.cpp
    ${SRC_DIR}/algorithm.cpp
    ${SRC_DIR}/optional.cpp
    ${SRC_DIR}/variant.cpp
    ${SRC_DIR}/any.cpp
    ${SRC_DIR}/generator.cpp
)

enable_testing()

add_executable(test_unit
    ${TST_DIR}/array.cpp
    # ${TST_DIR}/vector.cpp
    ${TST_DIR}/raw_vector.cpp
    ${TST_DIR}/stack.cpp
    ${TST_DIR}/raw_list.cpp
    ${TST_DIR}/optional.cpp
    ${TST_DIR}/variant.cpp
    ${TST_DIR}/any.cpp
    ${TST_DIR}/generator.cpp
)

target_link_libraries(test_unit toy_std boost_unit_test_framework)

# target_compile_definitions(test_unit PUBLIC BOOST_TEST_DYN_LINK)

add_test(test_all test_unit)
