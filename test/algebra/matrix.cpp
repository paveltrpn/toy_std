
#include <gtest/gtest.h>

import toy_std.algebra;

TEST(matrix2, range) {
    toy::algebra::matrix2d foo;

    EXPECT_EQ(2, foo.range());
    EXPECT_NE(1, foo.range());
    EXPECT_NE(3, foo.range());
}

TEST(matrix3, range) {
    toy::algebra::matrix3d foo;

    EXPECT_EQ(3, foo.range());
    EXPECT_NE(2, foo.range());
    EXPECT_NE(4, foo.range());
}

TEST(matrix2, idtt_and_subscript_operators) {
    toy::algebra::matrix2d test{};
    toy::algebra::matrix2d idtt2{ 1.0, 0.0, 0.0, 1.0 };

    for (auto i = 0; i < 4; ++i) {
        auto foo = test[i];
        auto bar = idtt2[i];
        EXPECT_TRUE(foo == bar);
    }

    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < 2; ++j) {
            auto foo = test[i, j];
            auto bar = idtt2[i, j];
            EXPECT_TRUE(foo == bar);
        }
    }
}

TEST(matrix3, idtt_and_subscript_operators) {
    toy::algebra::matrix3d test{};
    toy::algebra::matrix3d idtt2{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

    for (auto i = 0; i < 9; ++i) {
        auto foo = test[i];
        auto bar = idtt2[i];
        EXPECT_TRUE(foo == bar);
    }

    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            auto foo = test[i, j];
            auto bar = idtt2[i, j];
            EXPECT_TRUE(foo == bar);
        }
    }
}
