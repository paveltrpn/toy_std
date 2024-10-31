
#pragma once

#include <iostream>

namespace toy
{

namespace __detail
{

struct type_index final {
    [[nodiscard]] static std::size_t next() noexcept {
        // NOTE: possible atomic
        static long long value;
        return value++;
    }
};

} // namespace __detail

template <typename T> struct type_index final {
    [[nodiscard]] static std::size_t value() noexcept {
        static const std::size_t value = __detail::type_index::next();
        return value;
    }
};

} // namespace toy
