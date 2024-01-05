
import toy_std.raw_list;

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
}
#endif

BOOST_AUTO_TEST_SUITE(raw_list)

BOOST_AUTO_TEST_CASE(case_construct_push_pop) {
    toy::raw_list<std::string> first{};

    first.push_back("lisa");
    BOOST_CHECK_EQUAL(first.back(), "lisa");
    first.push_back("bob");
    BOOST_CHECK_EQUAL(first.back(), "bob");
    first.push_back("woody");
    BOOST_CHECK_EQUAL(first.back(), "woody");
    first.push_back("martin");
    BOOST_CHECK_EQUAL(first.back(), "martin");

    BOOST_CHECK(first.size() == 4);
    
    auto str = first.back();
    first.pop_back();
    BOOST_CHECK_EQUAL(str, "martin");

    str = first.back();
    first.pop_back();
    BOOST_CHECK_EQUAL(str, "woody");
    
    str = first.back();
    first.pop_back();
    BOOST_CHECK_EQUAL(str, "bob");
    
    str = first.back();
    first.pop_back();
    BOOST_CHECK_EQUAL(str, "lisa");

    BOOST_CHECK(first.size() == 0);

    first.push_front("lisa");
    BOOST_CHECK_EQUAL(first.front(), "lisa");
    first.push_front("bob");
    BOOST_CHECK_EQUAL(first.front(), "bob");
    first.push_front("woody");
    BOOST_CHECK_EQUAL(first.front(), "woody");
    first.push_front("martin");
    BOOST_CHECK_EQUAL(first.front(), "martin");

    BOOST_CHECK(first.size() == 4);
    
    str = first.front();
    first.pop_front();
    BOOST_CHECK_EQUAL(str, "martin");

    str = first.front();
    first.pop_front();
    BOOST_CHECK_EQUAL(str, "woody");
    
    str = first.front();
    first.pop_front();
    BOOST_CHECK_EQUAL(str, "bob");
    
    str = first.front();
    first.pop_front();
    BOOST_CHECK_EQUAL(str, "lisa");

    BOOST_CHECK(first.size() == 0);
}

BOOST_AUTO_TEST_CASE(case_range_for) {
    toy::raw_list<std::string> first;
    std::vector<std::string> tst{ "lisa", "bob", "woody", "martin" };

    for (auto &elem : tst) {
        first.push_back(elem);
    }

    for (size_t i = 0; auto &elem : first) {
        BOOST_CHECK_EQUAL(elem, tst[i]);
        ++i;
    }
}

BOOST_AUTO_TEST_SUITE_END()  // raw_list:
