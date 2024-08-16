
module;

#include <cstddef>
#include <initializer_list>

export module toy_std.algebra:matrix2;

import :matrix;

namespace toy::algebra {

template <typename T, size_t rng>
struct matrix2 final : public matrix_base<T, rng> {
        using base_type = matrix_base<T, rng>;
        using base_type::_data;
        using typename base_type::value_type;

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
};

export {
    using matrix2l = matrix2<long long, 2>;
    using matrix2d = matrix2<double, 2>;
}

}  // namespace toy::algebra
