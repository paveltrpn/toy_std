
import toy_std.algebra;
import toy_std.array;

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
    toy::algebra::matrix<float, 0, 0> mtrx0x0{};
    toy::algebra::matrix<float, 5, 0> mtrx5x0{};
    toy::algebra::matrix<float, 0, 5> mtrx0x5{};
    toy::algebra::matrix<int *, 6, 5> mtrx6x5{};
}
#endif

BOOST_AUTO_TEST_SUITE(matrix)

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(case_construct, *utf::tolerance(0.00001)) {
    toy::algebra::matrix4f one;

    one.set_idtt();

    auto dg0 = one[0, 0];
    auto dg1 = one[1, 1];
    auto dg2 = one[2, 2];
    auto dg3 = one[3, 3];

    BOOST_TEST(dg0 == 1.0);
    BOOST_TEST(dg1 == 1.0);
    BOOST_TEST(dg2 == 1.0);
    BOOST_TEST(dg3 == 1.0);

    auto zt = one[0, 3];
    auto to = one[2, 1];

    BOOST_TEST(zt == 0.0);
    BOOST_TEST(to == 0.0);
}

BOOST_AUTO_TEST_SUITE_END()
