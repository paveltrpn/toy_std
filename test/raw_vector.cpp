
#include <gtest/gtest.h>

import toy_std.raw_vector;

TEST(raw_vector, construct_push_pop) {
    toy::raw_vector<std::string> first{ 3, "nil" };

    EXPECT_EQ(first[1], "nil");

    first[0] = "ten";
    EXPECT_EQ(first[0], "ten");

    first[2] = std::string{ "thirty" };
    EXPECT_EQ(first[2], "thirty");

    auto foo = first.pop_back();
    EXPECT_EQ(foo, "thirty");
    EXPECT_EQ(first.size(), static_cast<size_t>(2));

    first.push_back("thirty");
    EXPECT_EQ(first[2], "thirty");
    EXPECT_EQ(first.size(), static_cast<size_t>(3));
}

TEST(raw_vector, construct_init_list_pop) {
    toy::raw_vector<std::string> initLst{ "first", "second", "third" };
    EXPECT_EQ(initLst[0], "first");
    EXPECT_EQ(initLst[1], "second");
    EXPECT_EQ(initLst[2], "third");
    EXPECT_EQ(initLst.size(), static_cast<size_t>(3));
    EXPECT_EQ(initLst.capacity(), static_cast<size_t>(3));
}

TEST(raw_vector, copy_create) {
    toy::raw_vector<int> first;

    first.push_back(10);
    first.push_back(30);

    toy::raw_vector<int> second{ first };

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[1], 30);
}

TEST(raw_vector, move_create) {
    toy::raw_vector<int> first;

    first.push_back(10);
    first.push_back(30);

    toy::raw_vector<int> second{ std::move(first) };

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[1], 30);

    EXPECT_EQ(first.size(), static_cast<size_t>(0));
    EXPECT_EQ(first.capacity(), static_cast<size_t>(0));
    EXPECT_EQ(first.data(), nullptr);
    EXPECT_NE(second.data(), nullptr);
}

TEST(raw_vector, copy_assign) {
    toy::raw_vector<int> first(1);
    toy::raw_vector<int> second(0);

    first.push_back(10);
    first.push_back(30);
    first.push_back(0);

    second = first;

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[1], 30);
    EXPECT_EQ(second[2], 0);
}

TEST(aw_vector, move_assign) {
    toy::raw_vector<int> first(1);
    toy::raw_vector<int> second(0);

    first.push_back(10);
    first.push_back(30);

    second = std::move(first);

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[1], 30);

    EXPECT_EQ(first.size(), static_cast<size_t>(0));
    EXPECT_EQ(first.capacity(), static_cast<size_t>(0));
    EXPECT_EQ(first.data(), nullptr);
    EXPECT_NE(second.data(), nullptr);
}

TEST(raw_vector, at) {
    toy::raw_vector<int> first(0);

    first.push_back(10);
    first.push_back(20);
    first.push_back(30);

    EXPECT_NO_THROW(first.at(2));
    EXPECT_THROW(first.at(4), std::invalid_argument);
}
