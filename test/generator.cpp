
#include <gtest/gtest.h>

#include <coroutine>

import toy_std.coroutines;

toy::Generator<int32_t> counter() {
    for ( int32_t i = 0; i < 3; ) {
        // equivalent to
        // co_await promise.yield_value(expr);
        // co_yield i;
        co_await i;
        i++;
    }
}

TEST( generator, generator ) {
    auto gen = counter();

    EXPECT_EQ( true, static_cast<bool>( gen ) );  // obviously we not done!
    EXPECT_EQ( 0, gen() );
    EXPECT_EQ( true, static_cast<bool>( gen ) );  // still not done!
    EXPECT_EQ( 1, gen() );
    EXPECT_EQ( true, static_cast<bool>( gen ) );  // still not done!
    EXPECT_EQ( 2, gen() );
    EXPECT_EQ( false, static_cast<bool>( gen ) );  // now done!
}
