
#define BOOST_TEST_MODULE test_unit

#include "../src/vector.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vector)

BOOST_AUTO_TEST_CASE(case_creation) {
    toy::vector<int> first{3, 11};

    BOOST_CHECK_EQUAL(first[1], 11);
    
    first[0] = 10;
    BOOST_CHECK_EQUAL(first[0], 10);
    
    first[2] = 30;
    BOOST_CHECK_EQUAL(first[2], 30);
}

BOOST_AUTO_TEST_CASE(case_copy_create) {
    toy::vector<int> first;

    first.push_back(10);
    first.push_back(30);
    
    toy::vector<int> second{first};

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);
}

BOOST_AUTO_TEST_CASE(case_copy_assign) {
    toy::vector<int> first{0};
    toy::vector<int> second{0};
    
    first.push_back(10);
    first.push_back(30);
    first.push_back(0);

    second = first;

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);
    BOOST_CHECK_EQUAL(second[2], 0);
}

BOOST_AUTO_TEST_CASE(case_at) {
    toy::vector<int> first{0};
    
    first.push_back(10);
    first.push_back(20);
    first.push_back(30);

    BOOST_CHECK_NO_THROW(first.at(2));
    BOOST_CHECK_THROW(first.at(4), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
