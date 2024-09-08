cmake_minimum_required(VERSION 3.28)

# When specifying an out-of-tree source a binary directory must be explicitly specified.
add_subdirectory(../third_party/googletest ../build)

enable_testing()

add_executable(test_unit 
    main.cpp
    array.cpp
    vector.cpp
    raw_vector.cpp
    raw_list.cpp
    stack.cpp
    optional.cpp
    variant.cpp
    any.cpp
    generator.cpp
    string.cpp
    algebra/matrix.cpp
    algebra/vector.cpp
    algebra/quaternion.cpp
)

target_link_libraries(test_unit gtest_main gmock_main toy_std)
add_test(NAME toy_std_test COMMAND test_unit)
