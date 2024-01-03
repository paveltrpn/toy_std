
import toy_stl.list;

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
}
#endif

BOOST_AUTO_TEST_SUITE(list)

BOOST_AUTO_TEST_CASE(case_construct_push_pop) {
    toy::list<std::string> first{};

    first.push("lisa");
    BOOST_CHECK_EQUAL(first.pop(), "lisa");

    first.push("bob");
    BOOST_CHECK_EQUAL(first.pop(), "bob");

    first.push("woody");
    BOOST_CHECK_EQUAL(first.pop(), "woody");

    first.push("martin");
    BOOST_CHECK_EQUAL(first.pop(), "martin");
}

BOOST_AUTO_TEST_CASE(case_range_for) {
    toy::list<std::string> first{};
    std::vector<std::string> tst{ "lisa", "bob", "woody", "martin" };

    for (auto &elem : tst) {
        first.push(elem);
    }

    for (auto elem : first) {
    }
}

BOOST_AUTO_TEST_SUITE_END()  // list
