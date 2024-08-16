module;

#include <cstddef>
#include <mdspan>

export module toy_std.algebra:matrix;

import toy_std.array;

namespace toy::algebra {

template <typename T, size_t rng>
struct matrix_base {
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        // row-wise indexing operator
        [[nodiscard]]
        reference operator[](size_t i, size_t j) {
            return std::mdspan(_data.data(), rng, rng)[i, j];
        }

        [[nodiscard]]
        const_reference operator[](size_t i, size_t j) const {
            return std::mdspan(_data.data(), rng, rng)[i, j];
        }

        [[nodiscard]]
        reference operator[](size_t index) {
            return _data[index];
        }

        [[nodiscard]]
        const_reference operator[](size_t index) const {
            return _data[index];
        }

        [[nodiscard]]
        size_t size() {
            return _data.size();
        }

        [[nodiscard]]
        consteval size_t range() {
            return rng;
        };

        [[nodiscard]]
        pointer data() {
            return _data.data();
        }

        [[nodiscard]]
        const_pointer data() const {
            return _data.data();
        }

    protected:
        toy::array<value_type, rng * rng> _data;
};

}  // namespace toy::algebra
