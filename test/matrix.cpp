
#include "../src/matrix.h"

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
    toy::math::matrix<float, 0, 0> mtrx0x0{};
    toy::math::matrix<float, 5, 0> mtrx5x0{};
    toy::math::matrix<float, 0, 5> mtrx0x5{};
}
#endif

BOOST_AUTO_TEST_SUITE(matrix)

BOOST_AUTO_TEST_CASE(case_construct) {
}

BOOST_AUTO_TEST_SUITE_END()
