
module;

#include <cstddef>
#include <cmath>

export module toy_std.algebra:vector;

import toy_std.array;

namespace toy::algebra {

export template <typename T, size_t size>
struct vector_base {
        using self = vector_base<T, size>;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        [[nodiscard]]
        reference operator[](size_t index) {
            return data_[index];
        }

        [[nodiscard]]
        const_reference operator[](size_t index) const {
            return data_[index];
        }

        void plus(const self &b) {
            for (size_t i = 0; i < size; ++i)
                data_[i] += b.data_[i];
        };

        void minus(const self &b) {
            for (size_t i = 0; i < size; ++i)
                data_[i] -= b.data_[i];
        };

        template <typename U>
        void scale(U factor) {
            for (size_t i = 0; i < size; ++i)
                data_[i] *= factor;
        }

        value_type dot(const self &b) const {
            value_type rt{};

            for (size_t i = 0; i < size; ++i)
                rt += data_[i] * b.data_[i];

            return rt;
        }

        value_type sqLenght() const {
            return dot(*this);
        }

        auto lenght() -> value_type const {
            return std::sqrt(sqLenght());
        }

    protected:
        toy::array<value_type, size> data_;
};

}  // namespace toy::algebra
