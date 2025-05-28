
#include <gtest/gtest.h>

#include <print>
#include <utility>

import toy_std.memory;

#define TEST_TYPE int

TEST( unique_ptr, default_construct ) {
    toy::unique_ptr<TEST_TYPE> foo{};
    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, construct ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo.get() );
    EXPECT_NE( 11, *foo.get() );
    foo.release();
    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, move_construct ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo.get() );
    EXPECT_NE( 11, *foo.get() );
    toy::unique_ptr<TEST_TYPE> bar{ std::move( foo ) };
    EXPECT_EQ( 10, *bar.get() );
    EXPECT_NE( 11, *bar.get() );

    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, move_assign ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo.get() );
    EXPECT_NE( 11, *foo.get() );

    toy::unique_ptr<TEST_TYPE> bar{};
    bar = std::move( foo );

    EXPECT_EQ( 10, *bar.get() );
    EXPECT_NE( 11, *bar.get() );

    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, release ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo.get() );
    EXPECT_NE( 11, *foo.get() );

    const auto bar = foo.release();
    EXPECT_EQ( 10, *bar );
    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, reset ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo.get() );
    EXPECT_NE( 11, *foo.get() );

    foo.reset( new TEST_TYPE{ 11 } );
    EXPECT_EQ( 11, *foo.get() );
    EXPECT_NE( 12, *foo.get() );

    foo.reset();
    EXPECT_EQ( nullptr, foo.get() );
}

TEST( unique_ptr, operators ) {
    toy::unique_ptr<TEST_TYPE> foo{ new TEST_TYPE{ 10 } };
    EXPECT_EQ( 10, *foo );
    EXPECT_NE( 11, *foo );

    bool tst{};
    if ( foo ) tst = true;
    EXPECT_EQ( true, tst );

    foo.release();
    if ( !foo ) tst = true;
    EXPECT_EQ( true, tst );
}

namespace {

void deleter_function( int *p ) {
    std::println( "pointer to function deleter called" );
    delete p;
}

void deleter_function_array( int *p ) {
    std::println( "pointer to function deleter array called" );
    delete[] p;
}

}  // namespace

TEST( unique_ptr, pointer_to_function_deleter ) {
    toy::unique_ptr<TEST_TYPE, void ( * )( int * )> foo{ new TEST_TYPE{ 10 },
                                                         deleter_function };
    EXPECT_EQ( 10, *foo );
    EXPECT_NE( 11, *foo );

    foo.reset( new TEST_TYPE{ 11 } );
    EXPECT_EQ( 11, *foo );
    EXPECT_NE( 12, *foo );
}

TEST( unique_ptr, pointer_to_function_deleter_move_assign ) {
    toy::unique_ptr<TEST_TYPE, decltype( &deleter_function )> foo{
        new TEST_TYPE{ 10 }, deleter_function };
    EXPECT_EQ( 10, *foo );
    EXPECT_NE( 11, *foo );

    toy::unique_ptr<TEST_TYPE, std::decay_t<decltype( deleter_function )>> bar{
        nullptr, deleter_function };
    bar = std::move( foo );

    EXPECT_EQ( 10, *bar );
    EXPECT_NE( 11, *bar );

    EXPECT_EQ( nullptr, foo.get() );
}

#define TEST_TYPE_ARRAY_SIZE 10

TEST( unique_ptr, pointer_to_function_deleter_array ) {
    toy::unique_ptr<TEST_TYPE, decltype( &deleter_function_array )> foo{
        new TEST_TYPE[TEST_TYPE_ARRAY_SIZE], deleter_function_array };

    auto fooPtr = foo.get();
    fooPtr[0] = 10;
    fooPtr[1] = 11;
    // UB
    // fooPtr[TEST_TYPE_ARRAY_SIZE] = 0;

    EXPECT_EQ( 10, fooPtr[0] );
    EXPECT_EQ( 11, fooPtr[1] );
}

TEST( unique_ptr, pointer_to_function_deleter_array_move_assign ) {
    toy::unique_ptr<TEST_TYPE, decltype( &deleter_function_array )> foo{
        new TEST_TYPE[10], deleter_function_array };

    auto fooPtr = foo.get();
    fooPtr[0] = 10;
    fooPtr[1] = 11;

    EXPECT_EQ( 10, fooPtr[0] );
    EXPECT_EQ( 11, fooPtr[1] );

    toy::unique_ptr<TEST_TYPE, std::decay_t<decltype( deleter_function_array )>>
        bar{ nullptr, deleter_function_array };

    bar = std::move( foo );
    auto barPtr = bar.get();

    EXPECT_EQ( 10, barPtr[0] );
    EXPECT_EQ( 11, barPtr[1] );

    EXPECT_EQ( nullptr, foo.get() );
}
