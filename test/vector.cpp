
import toy_std;

#include <string>

#define BOOST_NO_CXX98_FUNCTION_BASE
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
    BOOST_CHECK_EQUAL(first.size(), static_cast<size_t>(2));

    first.push_back("thirty");
    BOOST_CHECK_EQUAL(first[2], "thirty");
    BOOST_CHECK_EQUAL(first.size(), static_cast<size_t>(3));
}

BOOST_AUTO_TEST_CASE(case_construct_init_list) {
    toy::vector<std::string> initLst{ "first", "second", "third" };
    BOOST_CHECK_EQUAL(initLst[0], "first");
    BOOST_CHECK_EQUAL(initLst[1], "second");
    BOOST_CHECK_EQUAL(initLst[2], "third");
    BOOST_CHECK_EQUAL(initLst.size(), static_cast<size_t>(3));
    BOOST_CHECK_EQUAL(initLst.capacity(), static_cast<size_t>(3));
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

    BOOST_CHECK_EQUAL(first.size(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.capacity(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.data(), nullptr);
    BOOST_CHECK_NE(second.data(), nullptr);
}

BOOST_AUTO_TEST_CASE(case_copy_assign) {
    toy::vector<int> first(1);
    toy::vector<int> second(0);

    first.push_back(10);
    first.push_back(30);
    first.push_back(0);

    second = first;

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);
    BOOST_CHECK_EQUAL(second[2], 0);

    toy::vector<int> greter(5);
}

BOOST_AUTO_TEST_CASE(case_move_assign) {
    toy::vector<int> first(1);
    toy::vector<int> second(0);

    first.push_back(10);
    first.push_back(30);

    second = std::move(first);

    BOOST_CHECK_EQUAL(second[0], 10);
    BOOST_CHECK_EQUAL(second[1], 30);

    BOOST_CHECK_EQUAL(first.size(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.capacity(), static_cast<size_t>(0));
    BOOST_CHECK_EQUAL(first.data(), nullptr);
    BOOST_CHECK_NE(second.data(), nullptr);
}

BOOST_AUTO_TEST_CASE(case_at) {
    toy::vector<int> first(0);

    first.push_back(10);
    first.push_back(20);
    first.push_back(30);

    BOOST_CHECK_NO_THROW(first.at(2));
    BOOST_CHECK_THROW(first.at(4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(case_iterator) {
    toy::vector<int> first{ 0, 1, 2, 3, 4, 5, 6, 7 };

    for (size_t i = 0; auto& elem : first) {
        BOOST_CHECK_EQUAL(elem, i);
        ++i;
    }
}

BOOST_AUTO_TEST_CASE(case_const_iterator) {
    toy::vector<int> first{ 0, 1, 2, 3, 4, 5, 6, 7 };

    for (size_t i = 0; const auto& elem : first) {
        BOOST_CHECK_EQUAL(elem, i);
        ++i;
    }
}

BOOST_AUTO_TEST_CASE(case_std_sort) {
    toy::vector<int> sorted{ 0, 1, 2, 3, 4, 5, 6, 7 };
    toy::vector<int> raw{ 5, 2, 6, 7, 4, 3, 1, 0 };

    std::sort(raw.begin(), raw.end());

    for (size_t i = 0; i < 8; ++i) {
        BOOST_CHECK_EQUAL(raw[i], sorted[i]);
    }
}

BOOST_AUTO_TEST_CASE(case_std_for_each) {
    toy::vector<int> doubled{ 0, 1, 4, 9, 16, 25, 36 };
    toy::vector<int> raw{ 0, 1, 2, 3, 4, 5, 6 };

    std::for_each(raw.begin(), raw.end(), [](auto& elem) { elem *= elem; });

    for (size_t i = 0; i < 7; ++i) {
        BOOST_CHECK_EQUAL(raw[i], doubled[i]);
    }
}
BOOST_AUTO_TEST_SUITE_END()
