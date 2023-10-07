cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (toy_containers)

add_compile_options(-g -Wall -Wextra -Wpedantic -std=c++20 -stdlib=libc++ -Wno-unused-parameter)
add_link_options(-stdlib=libc++)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(WORK_DIR "/mnt/Fdisk_ext4_ssd_sata/code")
set(SRC_DIR "src")
set(TST_DIR "test")

# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

enable_testing()
set(Boost_INCLUDE_DIR "${WORK_DIR}/extern_libs/boost_1_83_0")
set(Boost_LIBRARY_DIR "${WORK_DIR}/extern_libs/boost_1_83_0/stage/lib")
find_package(Boost 1.80.0 COMPONENTS filesystem system unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(test_unit
    ${TST_DIR}/array.cpp
    ${TST_DIR}/vector.cpp)
target_link_libraries(test_unit ${Boost_LIBRARIES})
# target_compile_definitions(test_unit PUBLIC BOOST_TEST_DYN_LINK)

add_test(array test_unit)
