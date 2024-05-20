
#include <coroutine>

#define BOOST_TEST_DYN_LINK
#define BOOST_NO_CXX98_FUNCTION_BASE
#include <boost/test/unit_test.hpp>

import toy_std.generator;

toy::Generator<int32_t> counter() {
    for (int32_t i = 0; i < 3;) {
        co_yield i++;
    }
}

BOOST_AUTO_TEST_SUITE(generator)

BOOST_AUTO_TEST_CASE(case_generator) {
    auto gen = counter();
    while (gen) {
        std::cout << "counter: " << gen() << std::endl;
    }
}

BOOST_AUTO_TEST_SUITE_END()
