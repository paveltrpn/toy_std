
#include "coroutines.h"
#include <iostream>

toy::async_manual_reset_event event;
std::string value;

void producer() {
    value = "get_some_string_value";

    // Publish a value by setting the event.
    event.set();
}

// Can be called many times to create many tasks.
// All consumer tasks will wait until value has been published.
toy::task consumer() {
    // Wait until value has been published by awaiting event.
    co_await event;  // suspend point!!!
    std::cout << "consume value: " << value << "\n";
}

int main( int argc, char **argv ) {
    std::cout << "try to consume...\n";
    consumer();

    std::cout << "produce value...\n";
    producer();

    return 0;
}
