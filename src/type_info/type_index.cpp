
module;

#include <iostream>

export module toy_std.type_info:type_index;

namespace toy {

namespace __detail {

export struct type_index final {
    [[nodiscard]] static std::size_t next() noexcept {
        // NOTE: possible atomic
        static long long value;
        return value++;
    }
};

}  // namespace __detail

export template <typename T>
struct type_index final {
    [[nodiscard]] static std::size_t value() noexcept {
        static const std::size_t value = __detail::type_index::next();
        return value;
    }
};

}  // namespace toy
