
#include "../src/vector.h"
#include <string>

#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
    toy::vector<std::basic_string<wchar_t>> wcharSrt{ 3, L"nil" };
    toy::vector<std::basic_string<std::byte>> byteStr{ 1, "nil" };
    toy::vector<std::wstring> wstr{ 1, L"nil" };
    toy::vector<std::basic_string<char>> charStr{ 1, "nil" };
}
#endif

BOOST_AUTO_TEST_SUITE(vector)

BOOST_AUTO_TEST_CASE(case_construct_push_pop) {
    toy::vector<std::string> first{ 3, "nil" };

    BOOST_CHECK_EQUAL(first[1], "nil");

    first[0] = "ten";
    BOOST_CHECK_EQUAL(first[0], "ten");

    first[2] = std::string{ "thirty" };
    BOOST_CHECK_EQUAL(first[2], "thirty");

    auto foo = first.pop_back();
    BOOST_CHECK_EQUAL(foo, "thirty");
    BOOST_CHECK_EQUAL(first.getSize(), static_cast<size_t>(2));

    first.push_back("thirty");
    BOOST_CHECK_EQUAL(first[2], "thirty");
    BOOST_CHECK_EQUAL(first.getSize(), static_cast<size_t>(3));
}

BOOST_AUTO_TEST_CASE(case_copy_create, *boost::unit_test::tolerance(0.00001)) {
    toy::vector<float> first;

    first.push_back(10.0f);
    first.push_back(30.0f);

    toy::vector<float> second{ first };

    BOOST_TEST(second[0] == 10.0f);
    BOOST_TEST(second[1] == 30.0f);
}

BOOST_AUTO_TEST_CASE(case_move_create) {
    toy::vector<int> first;

    first.push_back(10);
    first.push_back(30);

    toy::vector<int> second{ std::move(first) };

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);

    BOOST_CHECK_EQUAL(first.getSize(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.getCap(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.getPtr(), nullptr);
    BOOST_CHECK_NE(second.getPtr(), nullptr);
}

BOOST_AUTO_TEST_CASE(case_copy_assign) {
    toy::vector<int> first{ 1 };
    toy::vector<int> second{ 0 };

    first.push_back(10);
    first.push_back(30);
    first.push_back(0);

    second = first;

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);
    BOOST_CHECK_EQUAL(second[2], 0);
}

BOOST_AUTO_TEST_CASE(case_at) {
    toy::vector<int> first{ 0 };

    first.push_back(10);
    first.push_back(20);
    first.push_back(30);

    BOOST_CHECK_NO_THROW(first.at(2));
    BOOST_CHECK_THROW(first.at(4), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
