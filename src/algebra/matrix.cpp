module;

#include <array>
#include <cstddef>

export module toy_std.algebra:matrix;

import toy_std.array;

namespace toy::algebra {

export template <typename T, size_t _rng>
struct matrix_base {
        using value_type = T;

        [[nodiscard]]
        value_type& operator[](size_t index) {
            return _data[index];
        }

        [[nodiscard]]
        const value_type& operator[](size_t index) const {
            return _data[index];
        }

        [[nodiscard]]
        size_t size() {
            return _data.size();
        }

        [[nodiscard]]
        value_type* data() {
            return _data.data();
        }

    protected:
        std::array<value_type, _rng * _rng> _data;
};

}  // namespace toy::algebra
