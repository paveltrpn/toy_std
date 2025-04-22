
#include <gtest/gtest.h>

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
