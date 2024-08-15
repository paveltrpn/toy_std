
#include <gtest/gtest.h>

import toy_std.stack;
import toy_std.vector;

TEST(stack, construct_push_pop) {
    toy::stack<int, toy::vector> first{ 10 };
}
