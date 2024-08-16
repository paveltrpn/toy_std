
module;

#include <cstddef>

export module toy_std.algebra:matrix3;

import :matrix;

namespace toy::algebra {

template <typename T>
struct matrix3 final : public matrix_base<T, 3> {
        using base_type = matrix_base<T, 3>;
        using typename base_type::value_type;
        // Introduce name _date from base_type namespace because of parent type is template.
        using base_type::_data;

        matrix3() {
            _data[0] = T{1.0};
            _data[1] = T{};
            _data[2] = T{};
            _data[3] = T{};
            _data[4] = T{1.0};
            _data[5] = T{};
            _data[6] = T{};
            _data[7] = T{};
            _data[8] = T{1.0};
        }
};

export {
    using matrix3l = matrix3<long long>;
    using matrix3d = matrix3<double>;
}

}  // namespace toy::algebra
