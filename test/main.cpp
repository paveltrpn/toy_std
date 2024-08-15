
#define BOOST_TEST_MODULE test_unit
#include <boost/test/unit_test.hpp>

void log_boost() {
    std::cout << "Using Boost " << BOOST_VERSION / 100000 << "."  // major version
              << BOOST_VERSION / 100 % 1000 << "."                // minor version
              << BOOST_VERSION % 100                              // patch level
              << std::endl;
}
