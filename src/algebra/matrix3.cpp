
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
};

export {
    using matrix3l = matrix3<long long>;
    using matrix3d = matrix3<double>;
}

}  // namespace toy::algebra
