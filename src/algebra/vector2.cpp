
module;

export module toy_std.algebra:vector2;

import :vector;

namespace toy::algebra {

export template <typename T>
struct vector2 : vector_base<T, 2> {
        using base_type = vector_base<T, 2>;
        using typename base_type::self;
        using base_type::data_;
        using typename base_type::value_type;

        vector2() {
            data_[0] = T{};
            data_[1] = T{};
        }

        vector2(value_type x, value_type y) {
            data_[0] = x;
            data_[1] = y;
        }
        
        vector2(const self &rhs) {
            (*this)[0] = rhs[0];
            (*this)[1] = rhs[1];
        }

        value_type x() {
            return data_[0];
        }

        value_type y() {
            return data_[1];
        }
};

export {
    using vevtor2l = vector2<long long>;
    using vevtor2d = vector2<double>;
}

}  // namespace toy::algebra
