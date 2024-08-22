
#include <gtest/gtest.h>

import toy_std.algebra;

// ==================================================================================
// ========================= matrix2 ================================================
// ==================================================================================
//
TEST(matrix2, range) {
    toy::algebra::matrix2d foo;

    EXPECT_EQ(2, foo.range());
    EXPECT_NE(1, foo.range());
    EXPECT_NE(3, foo.range());
}

TEST(matrix2, determinant) {
    toy::algebra::matrix2d foo{ 1.0, 2.0, 3.0, 5.0 };
    EXPECT_DOUBLE_EQ(-1.0, foo.determinant_lu());
}

TEST(matrix2, idtt_and_subscript_operators) {
    toy::algebra::matrix2d test{};
    toy::algebra::matrix2d idtt2{ 1.0, 0.0, 0.0, 1.0 };

    for (auto i = 0; i < 4; ++i) {
        auto foo = test[i];
        auto bar = idtt2[i];
        EXPECT_DOUBLE_EQ(foo, bar);
    }

    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < 2; ++j) {
            auto foo = test[i, j];
            auto bar = idtt2[i, j];
            EXPECT_DOUBLE_EQ(foo, bar);
        }
    }
}

TEST(matrix2, multiply) {
    auto A = toy::algebra::matrix2d{ -1.0, 2.0, -2.0, 3.0 };
    auto Aold = toy::algebra::matrix2d{ -1.0, 2.0, -2.0, 3.0 };
    auto B = toy::algebra::matrix2d{ 1.0, -2.0, 2.0, -3.0 };
    auto res = A * B;
    auto knownRes = toy::algebra::matrix2d{ 3.0, -4.0, 4.0, -5.0 };
    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 2; ++j) {
            auto foo = res[i, j];
            auto bar = knownRes[i, j];
            EXPECT_DOUBLE_EQ(foo, bar);
        }
}

// ==================================================================================
// ========================= matrix3 ================================================
// ==================================================================================

TEST(matrix3, range) {
    toy::algebra::matrix3d foo;

    EXPECT_EQ(3, foo.range());
    EXPECT_NE(2, foo.range());
    EXPECT_NE(4, foo.range());
}

TEST(matrix3, determinant) {
    toy::algebra::matrix3d foo{ 2.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 34.0, 55.0 };
    EXPECT_DOUBLE_EQ(-2.0, foo.determinant_lu());
}

TEST(matrix3, idtt_and_subscript_operators) {
    toy::algebra::matrix3d test{};
    toy::algebra::matrix3d idtt2{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

    for (auto i = 0; i < 9; ++i) {
        auto foo = test[i];
        auto bar = idtt2[i];
        EXPECT_DOUBLE_EQ(foo, bar);
    }

    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            auto foo = test[i, j];
            auto bar = idtt2[i, j];
            EXPECT_DOUBLE_EQ(foo, bar);
        }
    }
}

TEST(matrix3, mult) {
    toy::algebra::matrix3d fibo3{ 0.0, 1.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0 };
    toy::algebra::matrix3d fibo3_tr{ 0.0, 2.0, 8.0, 1.0, 3.0, 13.0, 1.0, 5.0, 21.0 };
    // fibo3_tr * fibo3
    toy::algebra::matrix3d mult3_tr{ 2.0, 8.0, 34.0, 8.0, 38.0, 160.0, 34.0, 160.0, 674.0 };

    toy::algebra::matrix3d one{ fibo3 };
    one.multiply(fibo3_tr);

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = one[i, j];
            auto bar = mult3_tr[i, j];
            EXPECT_DOUBLE_EQ(foo, bar);
        }
}

// ==================================================================================
// ========================= matrix4 ================================================
// ==================================================================================

TEST(matrix4, range) {
    toy::algebra::matrix4d foo;

    EXPECT_EQ(4, foo.range());
    EXPECT_NE(3, foo.range());
    EXPECT_NE(5, foo.range());
}

TEST(matrix4, determinant) {
    toy::algebra::matrix4d foo{ 1.0,  2.0,  3.0,   5.0,   8.0,   13.0,  21.0,  34.0,
                                55.0, 89.0, 144.0, 233.0, 377.0, 610.0, 987.0, 1597.0 };
    EXPECT_DOUBLE_EQ(-113400, foo.determinant_lu());
}

TEST(matrix4, compile) {
    toy::algebra::matrix4d euler{};
    euler.euler(100.0, 100.0, 100.0);
    EXPECT_TRUE(true);
}
