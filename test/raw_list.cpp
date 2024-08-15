 
#include <gtest/gtest.h>
#include <algorithm>

import toy_std.raw_list;

TEST(raw_list, construct_push_pop) {
    toy::raw_list<std::string> first{};

    first.push_back("lisa");
    EXPECT_EQ(first.back(), "lisa");
    first.push_back("bob");
    EXPECT_EQ(first.back(), "bob");
    first.push_back("woody");
    EXPECT_EQ(first.back(), "woody");
    first.push_back("martin");
    EXPECT_EQ(first.back(), "martin");

    EXPECT_TRUE(first.size() == 4);
    
    auto str = first.back();
    first.pop_back();
    EXPECT_EQ(str, "martin");

    str = first.back();
    first.pop_back();
    EXPECT_EQ(str, "woody");
    
    str = first.back();
    first.pop_back();
    EXPECT_EQ(str, "bob");
    
    str = first.back();
    first.pop_back();
    EXPECT_EQ(str, "lisa");

    EXPECT_TRUE(first.size() == 0);

    first.push_front("lisa");
    EXPECT_EQ(first.front(), "lisa");
    first.push_front("bob");
    EXPECT_EQ(first.front(), "bob");
    first.push_front("woody");
    EXPECT_EQ(first.front(), "woody");
    first.push_front("martin");
    EXPECT_EQ(first.front(), "martin");

    EXPECT_TRUE(first.size() == 4);
    
    str = first.front();
    first.pop_front();
    EXPECT_EQ(str, "martin");

    str = first.front();
    first.pop_front();
    EXPECT_EQ(str, "woody");
    
    str = first.front();
    first.pop_front();
    EXPECT_EQ(str, "bob");
    
    str = first.front();
    first.pop_front();
    EXPECT_EQ(str, "lisa");

    EXPECT_TRUE(first.size() == 0);
}

TEST(raw_list, range_for) {
    toy::raw_list<std::string> first;
    std::vector<std::string> tst{ "lisa", "bob", "woody", "martin" };

    for (auto &elem : tst) {
        first.push_back(elem);
    }

    for (size_t i = 0; auto &elem : first) {
        EXPECT_EQ(elem, tst[i]);
        ++i;
    }
}

TEST(raw_list, initializer_list_ctor) {
    toy::raw_list<std::string> first{"lisa", "bob", "woody", "martin"};
    std::vector<std::string> tst{ "lisa", "bob", "woody", "martin" };

    for (size_t i = 0; auto &elem : first) {
        EXPECT_EQ(elem, tst[i]);
        ++i;
    }
}
