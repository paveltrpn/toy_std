
import toy_std.array;

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE test_unit

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
    toy::array<float, 0> array0{};
}
#endif

BOOST_AUTO_TEST_SUITE(array)

BOOST_AUTO_TEST_CASE(case_creation) {
    toy::array<int, 3> first{ 0 };

    BOOST_CHECK_EQUAL(first[1], 0);

    first[0] = 10;
    BOOST_CHECK_EQUAL(first[0], 10);

    first[2] = 30;
    BOOST_CHECK_EQUAL(first[2], 30);
}

BOOST_AUTO_TEST_CASE(case_copy_create) {
    toy::array<int, 3> first{ 0 };

    first[0] = 10;
    first[2] = 30;

    toy::array<int, 3> second{ first };

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 0);
    BOOST_CHECK_EQUAL(second[2], 30);
}

BOOST_AUTO_TEST_CASE(case_copy_assign) {
    toy::array<int, 3> first{ 0 };
    toy::array<int, 3> second{ 0 };

    first[0] = 10;
    first[2] = 30;

    second = first;

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 0);
    BOOST_CHECK_EQUAL(second[2], 30);
}

BOOST_AUTO_TEST_CASE(case_at) {
    toy::array<int, 3> first{ 0 };

    BOOST_CHECK_NO_THROW(first.at(2));
    BOOST_CHECK_THROW(first.at(4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(case_c_style_pointer_get) {
    toy::array<int, 3> first{ 0, 1, 2, 3, 4, 5, 6, 7 };
    
    auto ptr = first.data();

    BOOST_CHECK_EQUAL(ptr[0], 0);
    BOOST_CHECK_EQUAL(ptr[1], 1);
    BOOST_CHECK_EQUAL(ptr[2], 2);
}

BOOST_AUTO_TEST_SUITE_END()
