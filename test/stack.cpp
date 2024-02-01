
import toy_std.stack;
import toy_std.vector;

#define BOOST_NO_CXX98_FUNCTION_BASE
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(stack)

BOOST_AUTO_TEST_CASE(case_construct_push_pop) {
    toy::stack<int, toy::vector> first{ 10 };
}

BOOST_AUTO_TEST_SUITE_END()  // stack
