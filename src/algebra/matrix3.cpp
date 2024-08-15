
module;

#include <cstddef>

export module toy_std.algebra:matrix3;

import :matrix;

namespace toy::algebra {

template <typename T>
struct matrix3 final : public matrix_base<T, 3> {
        using base_type = matrix_base<T, 3>;
        using typename base_type::value_type;
};

template <>
struct matrix3<double> final : matrix_base<double, 3> {
        using base_type = matrix_base<double, 3>;
        using typename base_type::value_type;

        matrix3() {
            _data[0] = 1.0;
            _data[1] = 0.0;
            _data[2] = 0.0;
            _data[3] = 0.0;
            _data[4] = 1.0;
            _data[5] = 0.0;
            _data[6] = 0.0;
            _data[7] = 0.0;
            _data[8] = 1.0;
        }
};

export using matrix3d = matrix3<double>;

}  // namespace toy::algebra
