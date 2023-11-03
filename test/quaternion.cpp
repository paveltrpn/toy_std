
#include "../src/quaternion.h"

#include <boost/test/unit_test.hpp>
#include "boost/test/unit_test_suite.hpp"

BOOST_AUTO_TEST_SUITE(quaternion)

BOOST_AUTO_TEST_CASE(case_construct) {
    toy::math::quaternion<int> first;

    BOOST_CHECK_EQUAL(first[0], 0);
    BOOST_CHECK_EQUAL(first[1], 0);
    BOOST_CHECK_EQUAL(first[2], 0);
    BOOST_CHECK_EQUAL(first[3], 0);

    toy::math::quaternion<int> second{ 1, 2, 3, 4 };

    BOOST_CHECK_EQUAL(second[0], 1);
    BOOST_CHECK_EQUAL(second[1], 2);
    BOOST_CHECK_EQUAL(second[2], 3);
    BOOST_CHECK_EQUAL(second[3], 4);

    toy::math::quaternion<int> fromQuat{ second };

    BOOST_CHECK_EQUAL(fromQuat[0], 1);
    BOOST_CHECK_EQUAL(fromQuat[1], 2);
    BOOST_CHECK_EQUAL(fromQuat[2], 3);
    BOOST_CHECK_EQUAL(fromQuat[3], 4);

    toy::array<int, 4> tstArr{ 1, 2, 3, 4 };
    toy::math::quaternion<int> fromArray{ tstArr };

    BOOST_CHECK_EQUAL(fromArray.x(), 1);
    BOOST_CHECK_EQUAL(fromArray.y(), 2);
    BOOST_CHECK_EQUAL(fromArray.z(), 3);
    BOOST_CHECK_EQUAL(fromArray.w(), 4);
}

BOOST_AUTO_TEST_CASE(case_assign) {
    toy::math::quaternion<int> first{ 1, 2, 3, 4 };
    toy::math::quaternion<int> second;
    
    second = first;
    
    BOOST_CHECK_NE(second.getData(), first.getData());
    BOOST_CHECK_EQUAL(second[0], 1);
    BOOST_CHECK_EQUAL(second[1], 2);
    BOOST_CHECK_EQUAL(second[2], 3);
    BOOST_CHECK_EQUAL(second[3], 4);
}

BOOST_AUTO_TEST_SUITE_END()