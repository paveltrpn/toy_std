
#include <boost/test/unit_test.hpp>
#include "boost/test/unit_test_suite.hpp"

import toy_std.algebra;

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(algebra_matrix)

BOOST_AUTO_TEST_CASE(case_matrix2_construct) {
    toy::algebra::matrix2d foo;

    BOOST_CHECK_EQUAL(4, foo.size());
}

BOOST_AUTO_TEST_CASE(case_matrix2_idtt, *utf::tolerance(0.00001)) {
    toy::algebra::matrix2d test{};
    toy::algebra::matrix2d idtt2{  1.0, 0.0, 0.0, 1.0  };

    for (auto i = 0; i < 4; ++i) {
        auto foo = test[i];
        auto bar = idtt2[i];
        BOOST_TEST(foo == bar);
    }
}

BOOST_AUTO_TEST_CASE(case_matrix3_construct) {
    toy::algebra::matrix3d foo;

    BOOST_CHECK_EQUAL(9, foo.size());
}

BOOST_AUTO_TEST_SUITE_END()
