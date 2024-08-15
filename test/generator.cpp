
#include <gtest/gtest.h>
#include <coroutine>

import toy_std.generator;

toy::Generator<int32_t> counter() {
    for (int32_t i = 0; i < 3;) {
        co_yield i++;
    }
}

TEST(generator, generator) {
    auto gen = counter();

    EXPECT_EQ(1, gen());
    EXPECT_EQ(2, gen());
}
