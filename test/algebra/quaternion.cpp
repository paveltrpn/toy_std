

#include <gtest/gtest.h>

import toy_std.algebra;

TEST(quaterniond, construct) {
    toy::algebra::quaterniond first;

    EXPECT_DOUBLE_EQ(first[0], 0.0);
    EXPECT_DOUBLE_EQ(first[1], 0.0);
    EXPECT_DOUBLE_EQ(first[2], 0.0);
    EXPECT_DOUBLE_EQ(first[3], 0.0);

    toy::algebra::quaterniond second{ 1.0, 2.0, 3.0, 4.0 };

    EXPECT_DOUBLE_EQ(second[0], 1.0);
    EXPECT_DOUBLE_EQ(second[1], 2.0);
    EXPECT_DOUBLE_EQ(second[2], 3.0);
    EXPECT_DOUBLE_EQ(second[3], 4.0);

    toy::algebra::quaterniond fromQuat{ second };

    EXPECT_DOUBLE_EQ(fromQuat[0], 1.0);
    EXPECT_DOUBLE_EQ(fromQuat[1], 2.0);
    EXPECT_DOUBLE_EQ(fromQuat[2], 3.0);
    EXPECT_DOUBLE_EQ(fromQuat[3], 4.0);

    std::array<double, 4> tstArr{ 1.0, 2.0, 3.0, 4.0 };
    toy::algebra::quaterniond fromArray{ tstArr };

    EXPECT_DOUBLE_EQ(fromArray.x(), 1.0);
    EXPECT_DOUBLE_EQ(fromArray.y(), 2.0);
    EXPECT_DOUBLE_EQ(fromArray.z(), 3.0);
    EXPECT_DOUBLE_EQ(fromArray.w(), 4.0);
}

TEST(quaterniond, assign) {
    toy::algebra::quaterniond first{ 1.0, 2.0, 3.0, 4.0 };
    toy::algebra::quaterniond second;

    second = first;

    EXPECT_NE(second.data(), first.data());
    EXPECT_DOUBLE_EQ(second[0], 1.0);
    EXPECT_DOUBLE_EQ(second[1], 2.0);
    EXPECT_DOUBLE_EQ(second[2], 3.0);
    EXPECT_DOUBLE_EQ(second[3], 4.0);
}

TEST(quaterniond, arithmetics) {
    toy::algebra::quaterniond first{ 1.0, 2.0, 3.0, 4.0 };
    toy::algebra::quaterniond second{ 10.0, 20.0, 30.0, 40.0 };

    auto sum{ second + first };

    EXPECT_DOUBLE_EQ(sum.x(), 10.0 + 1.0);
    EXPECT_DOUBLE_EQ(sum.y(), 20.0 + 2.0);
    EXPECT_DOUBLE_EQ(sum.z(), 30.0 + 3.0);
    EXPECT_DOUBLE_EQ(sum.w(), 40.0 + 4.0);

    auto sum2{ second };
    sum2 += first;

    EXPECT_DOUBLE_EQ(sum.x(), 10.0 + 1.0);
    EXPECT_DOUBLE_EQ(sum.y(), 20.0 + 2.0);
    EXPECT_DOUBLE_EQ(sum.z(), 30.0 + 3.0);
    EXPECT_DOUBLE_EQ(sum.w(), 40.0 + 4.0);

    auto sub{ second - first };

    EXPECT_DOUBLE_EQ(sub.x(), 10.0 - 1.0);
    EXPECT_DOUBLE_EQ(sub.y(), 20.0 - 2.0);
    EXPECT_DOUBLE_EQ(sub.z(), 30.0 - 3.0);
    EXPECT_DOUBLE_EQ(sub.w(), 40.0 - 4.0);

    auto sub2{ second };
    sub2 -= first;

    EXPECT_DOUBLE_EQ(sub.x(), 10.0 - 1.0);
    EXPECT_DOUBLE_EQ(sub.y(), 20.0 - 2.0);
    EXPECT_DOUBLE_EQ(sub.z(), 30.0 - 3.0);
    EXPECT_DOUBLE_EQ(sub.w(), 40.0 - 4.0);
}
