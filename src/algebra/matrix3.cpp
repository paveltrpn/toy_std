
module;

#include <cstddef>
#include <initializer_list>

export module toy_std.algebra:matrix3;

import :matrix;

namespace toy::algebra {

template <typename T, size_t rng = 3>
struct matrix3 final : public matrix_base<T, rng> {
        using base_type = matrix_base<T, rng>;
        using typename base_type::value_type;
        using self = matrix3<value_type, 3>;
        // Introduce name _data from matrix_base namespace because of parent type is template.
        using base_type::_data;

        matrix3() {
            _data[0] = T{ 1 };
            _data[1] = T{};
            _data[2] = T{};
            _data[3] = T{};
            _data[4] = T{ 1 };
            _data[5] = T{};
            _data[6] = T{};
            _data[7] = T{};
            _data[8] = T{ 1 };
        }

        matrix3(std::initializer_list<value_type> list) {
            for (auto i = 0; const auto e : list) {
                _data[i] = e;
                ++i;
            }
        }

        void multiply(const self& rhs) {
            auto this00 = (*this)[0, 0];
            auto this01 = (*this)[0, 1];

            (*this)[0, 0] = this00 * rhs[0, 0] + this01 * rhs[1, 0] + (*this)[0, 2] * rhs[2, 0];
            (*this)[0, 1] = this00 * rhs[0, 1] + this01 * rhs[1, 1] + (*this)[0, 2] * rhs[2, 1];
            (*this)[0, 2] = this00 * rhs[0, 2] + this01 * rhs[1, 2] + (*this)[0, 2] * rhs[2, 2];

            auto this10 = (*this)[1, 0];
            auto this11 = (*this)[1, 1];

            (*this)[1, 0] = this10 * rhs[0, 0] + this11 * rhs[1, 0] + (*this)[1, 2] * rhs[2, 0];
            (*this)[1, 1] = this10 * rhs[0, 1] + this11 * rhs[1, 1] + (*this)[1, 2] * rhs[2, 1];
            (*this)[1, 2] = this10 * rhs[0, 2] + this11 * rhs[1, 2] + (*this)[1, 2] * rhs[2, 2];

            auto this20 = (*this)[2, 0];
            auto this21 = (*this)[2, 1];

            (*this)[2, 0] = this20 * rhs[0, 0] + this21 * rhs[1, 0] + (*this)[2, 2] * rhs[2, 0];
            (*this)[2, 1] = this20 * rhs[0, 1] + this21 * rhs[1, 1] + (*this)[2, 2] * rhs[2, 1];
            (*this)[2, 2] = this20 * rhs[0, 2] + this21 * rhs[1, 2] + (*this)[2, 2] * rhs[2, 2];
        }

        value_type determinant() {
        }
};

export {
    using matrix3l = matrix3<long long>;
    using matrix3d = matrix3<double>;
}

}  // namespace toy::algebra
