
module;

#include <cstddef>
#include <initializer_list>
#include <cmath>

export module toy_std.algebra:matrix3;

import :matrix;

namespace toy::algebra {

export template <typename T, size_t rng = 3>
struct matrix3 final : public matrix_base<T, rng> {
        using base_type = matrix_base<T, rng>;
        using typename base_type::value_type;
        using self = matrix3<value_type, 3>;
        // Introduce name _data from matrix_base namespace because of parent type is template.
        using base_type::_data;

        matrix3() {
            idtt();
        }

        void zero() {
            _data[0] = T{};
            _data[1] = T{};
            _data[2] = T{};
            _data[3] = T{};
            _data[4] = T{};
            _data[5] = T{};
            _data[6] = T{};
            _data[7] = T{};
            _data[8] = T{};
        }

        void idtt() {
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

        void rotation(value_type yaw, value_type pitch, value_type roll) {
            auto siny = std::sin(yaw);
            auto cosy = std::cos(yaw);
            auto sinp = std::sin(pitch);
            auto cosp = std::cos(pitch);
            auto sinr = std::sin(roll);
            auto cosr = std::cos(roll);

            (*this)[0] = cosy * cosr - siny * cosp * sinr;
            (*this)[1] = -cosy * sinr - siny * cosp * cosr;
            (*this)[2] = siny * sinp;

            (*this)[3] = siny * cosr + cosy * cosp * sinr;
            (*this)[4] = -siny * sinr + cosy * cosp * cosr;
            (*this)[5] = -cosy * sinp;

            (*this)[6] = sinp * sinr;
            (*this)[7] = sinp * cosr;
            (*this)[8] = cosp;
        }
};

export {
    using matrix3l = matrix3<long long>;
    using matrix3d = matrix3<double>;
}

}  // namespace toy::algebra
