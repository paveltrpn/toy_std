cmake_minimum_required(VERSION 3.28)

# Set variable that define wheather toy_std build as submodule or not.
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(NOT_AS_MODULE false)
else()
    set(NOT_AS_MODULE true)
endif()

# If it standalone build then set compiler.
if (NOT_AS_MODULE)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    add_compile_options(-g 
                    -Wall 
                    -Wextra 
                    -Wpedantic 
                    -stdlib=libc++
                    -Wno-unused-parameter)

    add_link_options(-stdlib=libc++)
endif()

project (toy_std)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_SCAN_FOR_MODULES)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

option(WITH_UBSAN "build with undefined behavior sanitizer" OFF)
option(WITH_ASAN  "build with address sanitizer" OFF)
option(WITH_TSAN  "build with thread sanitizer" OFF)
option(WITH_MSAN  "build with memory sanitizer" OFF)

include_directories("src")

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

add_library(toy_std)
target_sources(toy_std
  PUBLIC
    FILE_SET CXX_MODULES FILES
    src/concepts.cpp
    src/array.cpp
    src/raw_list.cpp
    src/stack.cpp
    src/vector.cpp
    src/raw_vector.cpp
    src/iterator_traits.cpp
    src/toy_std.cpp
    src/algorithm.cpp
    src/string.cpp
    src/any.cpp
    src/variant.cpp
    src/optional.cpp
    src/tuple.cpp
    src/type_info/type_info.cpp
    src/type_info/type_name.cpp
    src/type_info/type_index.cpp
    src/type_info/registry.cpp
    src/memory/memory.cpp
    src/memory/unique_ptr.cpp
    src/memory/shared_ptr.cpp
    src/memory/deleters.cpp
    src/coroutines/coroutines.cpp
    src/coroutines/generator.cpp
    src/coroutines/async_manual_reset_event.cpp
)

# If it standalone build then need to build tests as well.
if (NOT_AS_MODULE)
    add_subdirectory(test)
endif()


