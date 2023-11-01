cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (toy_containers)

add_compile_options(-g 
                    -Wall 
                    -Wextra 
                    -Wpedantic 
                    -std=c++20 
                    -stdlib=libc++ 
                    -Wno-unused-parameter)

add_link_options(-stdlib=libc++)

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

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(WORK_DIR "/mnt/Fdisk_ext4_ssd_sata/code")
set(SRC_DIR "src")
set(TST_DIR "test")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

enable_testing()
set(Boost_INCLUDE_DIR "${WORK_DIR}/extern_libs/boost_1_83_0")
set(Boost_LIBRARY_DIR "${WORK_DIR}/extern_libs/boost_1_83_0/stage/lib")
find_package(Boost 1.80.0 COMPONENTS filesystem system unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(test_unit
    ${TST_DIR}/array.cpp
    ${TST_DIR}/vector.cpp
    ${TST_DIR}/raw_vector.cpp
    ${TST_DIR}/stack.cpp
    ${TST_DIR}/matrix.cpp
    ${TST_DIR}/mvector.cpp
    ${TST_DIR}/quaternion.cpp)

target_link_libraries(test_unit ${Boost_LIBRARIES})
# target_compile_definitions(test_unit PUBLIC BOOST_TEST_DYN_LINK)

add_test(array test_unit)
