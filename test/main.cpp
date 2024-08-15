
#define BOOST_TEST_MODULE test_unit
#include <boost/test/unit_test.hpp>

int main(int argc, char **argv) {
    std::cout << "Using Boost "
              << BOOST_VERSION / 100000     << "."  // major version
              << BOOST_VERSION / 100 % 1000 << "."  // minor version
              << BOOST_VERSION % 100                // patch level
              << std::endl;
}
