
import toy_std.algebra;

#define BOOST_NO_CXX98_FUNCTION_BASE
#include <boost/test/unit_test.hpp>
#include <cmath>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(mvector)

BOOST_AUTO_TEST_CASE(case_construct_and_arithmetic, *utf::tolerance(0.00001)) {
    toy::algebra::vector3f one{ 0.0f, 1.0f, 2.0f };

    BOOST_TEST(one.x() == 0.0f);
    BOOST_TEST(one.y() == 1.0f);
    BOOST_TEST(one.z() == 2.0f);

    toy::algebra::vector3f two{ 1.0f, 1.0f, 1.0f };
    two.sum_self(one);

    BOOST_TEST(two.x() == 1.0f);
    BOOST_TEST(two.y() == 2.0f);
    BOOST_TEST(two.z() == 3.0f);

    BOOST_TEST(two.length() == sqrt(14.0f));

    // auto cr = two.cross(one);
}

BOOST_AUTO_TEST_SUITE_END()
