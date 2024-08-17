

#include <gtest/gtest.h>
#include <cmath>

import toy_std.algebra;

TEST(vector, vector_construct_and_arithmetic) {
    constexpr size_t __SZ = 5;
    toy::algebra::vector_base<double, __SZ> one{ 0.0, 1.0, 2.0, 3.0, 4.0 };
    toy::algebra::vector_base<double, __SZ> two{ 0.0, 0.0, 0.0, 0.0, 0.0 };
    toy::algebra::vector_base<double, __SZ> three{ 1.0, 1.0, 1.0, 1.0, 1.0 };

    for (size_t i = 0; i < __SZ; ++i) {
        EXPECT_DOUBLE_EQ(two[i], 0.0);
        EXPECT_DOUBLE_EQ(three[i], 1.0);
    }

    toy::algebra::vector_base<double, __SZ> four = three;
    four = two + three;

    for (size_t i = 0; i < __SZ; ++i) {
        EXPECT_DOUBLE_EQ(four[i], 1.0);
    }

    // toy::algebra::vector<int, __SZ> intv{ 1, 1, 1, 1, 1 };
    // auto l = intv.lenght();
    // three = one + two;
}

TEST(vector2, construct_and_arithmetic) {
    toy::algebra::vector2d one{ 0.0, 1.0 };

    EXPECT_DOUBLE_EQ(one.x(), 0.0);
    EXPECT_DOUBLE_EQ(one.y(), 1.0);

    toy::algebra::vector2d two{ 1.0, 1.0 };
    two.plus(one);

    EXPECT_DOUBLE_EQ(two.x(), 1.0);
    EXPECT_DOUBLE_EQ(two.y(), 2.0);

    toy::algebra::vector2d three{ 0.0, 0.0 };
    three = one;

    EXPECT_DOUBLE_EQ(three.x(), one.x());
    EXPECT_DOUBLE_EQ(three.y(), one.y());

    auto lenght = two.sqLenght();

    EXPECT_DOUBLE_EQ(lenght, 5.0);

    toy::algebra::vector2d four = one + two + three;

    EXPECT_DOUBLE_EQ(four.x(), 1.0);
    EXPECT_DOUBLE_EQ(four.y(), 4.0);
}

TEST(vector3, vector3_construct_and_arithmetic) {
    toy::algebra::vector3d one{ 0.0, 1.0, 2.0 };

    EXPECT_DOUBLE_EQ(one.x(), 0.0);
    EXPECT_DOUBLE_EQ(one.y(), 1.0);
    EXPECT_DOUBLE_EQ(one.z(), 2.0);

    toy::algebra::vector3d two{ 1.0, 1.0, 1.0 };
    two.plus(one);

    EXPECT_DOUBLE_EQ(two.x(), 1.0);
    EXPECT_DOUBLE_EQ(two.y(), 2.0);
    EXPECT_DOUBLE_EQ(two.z(), 3.0);

    toy::algebra::vector3d three{ 0.0, 0.0, 0.0 };
    three = one;

    EXPECT_DOUBLE_EQ(three.x(), one.x());
    EXPECT_DOUBLE_EQ(three.y(), one.y());
    EXPECT_DOUBLE_EQ(three.z(), one.z());

    auto lenght = three.sqLenght();

    EXPECT_DOUBLE_EQ(lenght, 5.0);

    toy::algebra::vector3d four = one + two + three;

    EXPECT_DOUBLE_EQ(four.x(), 1.0);
    EXPECT_DOUBLE_EQ(four.y(), 4.0);
    EXPECT_DOUBLE_EQ(four.z(), 7.0);

    // auto cr = two.cross(one);
}
