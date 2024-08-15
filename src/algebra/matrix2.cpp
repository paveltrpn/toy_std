
module;

#include <cstddef>
#include <initializer_list>

export module toy_std.algebra:matrix2;

import :matrix;

namespace toy::algebra {

template <typename T>
struct matrix2 final : public matrix_base<T, 3> {
        using base_type = matrix_base<T, 3>;
        using typename base_type::value_type;
};

template <>
struct matrix2<double> final : matrix_base<double, 2> {
        using base_type = matrix_base<double, 2>;
        using typename base_type::value_type;

        matrix2() {
            _data[0] = 1.0;
            _data[1] = 0.0;
            _data[2] = 0.0;
            _data[3] = 1.0;
        }

        matrix2(std::initializer_list<value_type> list) {
            for (auto i = 0; const auto e : list) {
                _data[i] = e;
                ++i;
            }
        }
};

export using matrix2d = matrix2<double>;

}  // namespace toy::algebra
