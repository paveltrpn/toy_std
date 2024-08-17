
module;

#include <cstddef>
#include <initializer_list>

export module toy_std.algebra:matrix2;

import :matrix;

namespace toy::algebra {

export template <typename T, size_t rng = 2>
struct matrix2 final : public matrix_base<T, rng> {
        using base_type = matrix_base<T, rng>;
        using typename base_type::value_type;
        using self = matrix2<value_type, 2>;
        using base_type::_data;

        matrix2() {
            _data[0] = T{ 1 };
            _data[1] = T{};
            _data[2] = T{};
            _data[3] = T{ 1 };
        }

        matrix2(std::initializer_list<value_type> list) {
            for (auto i = 0; const auto e : list) {
                _data[i] = e;
                ++i;
            }
        }

        void multiply(const self &rhs) {
            auto data0 = (*this)[0];
            auto data1 = (*this)[1];
            (*this)[0] = rhs[0] * (*this)[0] + rhs[1] * (*this)[2];
            (*this)[1] = rhs[0] * (*this)[1] + rhs[1] * (*this)[3];
            (*this)[2] = rhs[2] * data0 + rhs[3] * (*this)[2];
            (*this)[3] = rhs[2] * data1 + rhs[3] * (*this)[3];
        }

        self operator*(const self &rhs) {
            auto tmp{ *this };
            tmp.multiply(rhs);
            return tmp;
        }

        value_type determinant() {
            return _data[0] * _data[3] - _data[2] * _data[1];
        }
};

export {
    using matrix2l = matrix2<long long, 2>;
    using matrix2d = matrix2<double, 2>;
}

}  // namespace toy::algebra
