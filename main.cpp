
#include <iostream>
#include <format>
#include <string>

#include "vector.h"
#include "raw_vector.h"

void test_vector() {
    std::cout << std::format("test_vector\n");

    toy::vector<int> foo;

    foo.push_back(1);
    foo.push_back(2);
    foo.push_back(3);

    std::cout << std::format("first - {} second - {} third - {}\n", foo[0], foo[1], foo[2]);
}

void test_raw_vector() {
    std::cout << std::format("test_raw_vector\n");

    toy::raw_vector<std::string> foo{};

    foo.push_back("one");
    foo.push_back("two");
    foo.push_back("three");

    std::cout << std::format("first - {} second - {} third - {}\n", foo[0], foo[1], foo[2]);
}

int main(int argc, char *argv[]) {
    std::cout << std::format("toy contsiners\n");

    test_vector();
    test_raw_vector();

    return 0;
}
