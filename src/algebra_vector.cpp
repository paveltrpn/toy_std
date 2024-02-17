
module;

#include <cstddef>
#include <initializer_list>
#include <cmath>

export module toy_std.algebra:vector;

import toy_std.concepts;
import toy_std.array;

namespace toy::algebra {

static constexpr size_t __SZ2 = 2;
static constexpr size_t __SZ3 = 3;
static constexpr size_t __SZ4 = 4;

template <typename T>
struct lenght_type {
        using type = float;
};

template <>
struct lenght_type<int> {
        using type = float;
};

template <>
struct lenght_type<double> {
        using type = double;
};

template <>
struct lenght_type<long double> {
        using type = long double;
};

template <template <typename> typename derived, toy::Arithmetical T, size_t pSize_>
struct vector_base {
        using self = vector_base<derived, T, pSize_>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        vector_base() = default;
        vector_base(const self& rhs) = default;
        vector_base(self&& rhs) = default;

        vector_base(std::initializer_list<value_type> list) {
            for (size_t i = 0; auto&& elem : list) {
                if (i > pSize_)
                    break;
                data_[i] = elem;
                ++i;
            }
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        value_type& operator[](size_t id) {
            return data_[id];
        }

        void sum(const self& b) {
            for (size_t i = 0; i < pSize_; ++i)
                data_[i] += b.data_[i];
        };

        void sub(const self& b) {
            for (size_t i = 0; i < pSize_; ++i)
                data_[i] -= b.data_[i];
        };

        template <toy::FloatingPoint U>
        void scale(U factor) {
            for (size_t i = 0; i < pSize_; ++i)
                data_[i] *= factor;
        }

        value_type dot(const self& b) const {
            value_type rt{};

            for (size_t i = 0; i < pSize_; ++i)
                rt += data_[i] * b.data_[i];

            return rt;
        }

        value_type sqLenght() const {
            return dot(*this);
        }

        auto lenght() -> typename lenght_type<value_type>::type const {
            return std::sqrt(sqLenght());
        }

        void noramlize() {
            auto len = lenght();

            // check len != 0

            for (auto& elem : data_) {
                elem /= len;
            }
        }

        void inverse() {
            for (auto& elem : data_) {
                elem = -elem;
            }
        }

        friend self operator+(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sum(rhs);
            return rt;
        }

        self& operator+=(const self& rhs) {
            (*this).sum(rhs);
            return *this;
        }

        friend self operator-(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sub(rhs);
            return rt;
        }

        self& operator-=(const self& rhs) {
            (*this).sub(rhs);
            return *this;
        }

        template <toy::FloatingPoint U>
        friend self operator*(const self& lhs, U factor) {
            auto rt = lhs;
            rt.scale(factor);
            return rt;
        }

        template <toy::FloatingPoint U>
        self& operator*=(U factor) {
            (*this).scale(factor);
            return *this;
        }

        friend self operator*(const self& lhs, const self& rhs) {
            auto rt = *lhs;
            rt.dot(rhs);
            return rt;
        }

        self& operator*=(const self& rhs) {
            (*this).dot(rhs);
            return *this;
        }

        toy::array<T, pSize_> data_;
};

template <toy::Arithmetical T>
struct vector2 : vector_base<vector2, T, __SZ2> {
        using self = vector2<T>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        using vector_base<vector2, T, __SZ2>::data_;

        vector2() = default;
        vector2(const self& rhs) = default;
        vector2(self&& rhs) = default;

        explicit vector2(value_type x, value_type y) {
            data_[0] = x;
            data_[1] = y;
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~vector2() = default;

        [[nodiscard]]
        value_type x() const {
            return data_[0];
        }

        [[nodiscard]]
        value_type y() const {
            return data_[1];
        }

        friend self operator+(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sum(rhs);
            return rt;
        }

        self& operator+=(const self& rhs) {
            (*this).sum(rhs);
            return *this;
        }

        friend self operator-(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sub(rhs);
            return rt;
        }

        self& operator-=(const self& rhs) {
            (*this).sub(rhs);
            return *this;
        }

        template <toy::FloatingPoint U>
        friend self operator*(const self& lhs, U factor) {
            auto rt = lhs;
            rt.scale(factor);
            return rt;
        }

        template <toy::FloatingPoint U>
        self& operator*=(U factor) {
            (*this).scale(factor);
            return *this;
        }

        friend self operator*(const self& lhs, const self& rhs) {
            auto rt = *lhs;
            rt.dot(rhs);
            return rt;
        }

        self& operator*=(const self& rhs) {
            (*this).dot(rhs);
            return *this;
        }
};

// vector3
template <toy::Arithmetical T>
struct vector3 : vector_base<vector3, T, __SZ3> {
        using self = vector3<T>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        using vector_base<vector3, T, __SZ3>::data_;

        vector3() = default;
        vector3(const self& rhs) = default;
        vector3(self&& rhs) = default;

        explicit vector3(value_type x, value_type y, value_type z) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~vector3() = default;

        [[nodiscard]]
        value_type x() const {
            return data_[0];
        }

        [[nodiscard]]
        value_type y() const {
            return data_[1];
        }

        [[nodiscard]]
        value_type z() const {
            return data_[2];
        }

        friend self operator+(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sum(rhs);
            return rt;
        }

        self& operator+=(const self& rhs) {
            (*this).sum(rhs);
            return *this;
        }

        friend self operator-(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sub(rhs);
            return rt;
        }

        self& operator-=(const self& rhs) {
            (*this).sub(rhs);
            return *this;
        }

        template <toy::FloatingPoint U>
        friend self operator*(const self& lhs, U factor) {
            auto rt = lhs;
            rt.scale(factor);
            return rt;
        }

        template <toy::FloatingPoint U>
        self& operator*=(U factor) {
            (*this).scale(factor);
            return *this;
        }

        friend self operator*(const self& lhs, const self& rhs) {
            auto rt = *lhs;
            rt.dot(rhs);
            return rt;
        }

        self& operator*=(const self& rhs) {
            (*this).dot(rhs);
            return *this;
        }

        void cross(self b) {
            *this = { data_[1] * b[2] - data_[2] * b[1],
                      data_[2] * b[0] - data_[0] * b[2],
                      data_[0] * b[1] - data_[1] * b[0] };
        }

        self operator^(const self& rhs) {
            auto rt = *this;
            rt.cross(rhs);
            return rt;
        }
};

template <toy::Arithmetical T>
struct vector4 : vector_base<vector4, T, __SZ4> {
        using self = vector4<T>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        using vector_base<vector4, T, __SZ4>::data_;

        vector4() = default;
        vector4(const self& rhs) = default;
        vector4(self&& rhs) = default;

        explicit vector4(value_type x, value_type y, value_type z, value_type w) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
            data_[3] = w;
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~vector4() = default;

        [[nodiscard]] value_type x() const {
            return data_[0];
        }

        [[nodiscard]] value_type y() const {
            return data_[1];
        }

        [[nodiscard]] value_type z() const {
            return data_[2];
        }

        [[nodiscard]] value_type w() const {
            return data_[3];
        }

        friend self operator+(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sum(rhs);
            return rt;
        }

        self& operator+=(const self& rhs) {
            (*this).sum(rhs);
            return *this;
        }

        friend self operator-(const self& lhs, const self& rhs) {
            auto rt = lhs;
            rt.sub(rhs);
            return rt;
        }

        self& operator-=(const self& rhs) {
            (*this).sub(rhs);
            return *this;
        }

        template <toy::FloatingPoint U>
        friend self operator*(const self& lhs, U factor) {
            auto rt = lhs;
            rt.scale(factor);
            return rt;
        }

        template <toy::FloatingPoint U>
        self& operator*=(U factor) {
            (*this).scale(factor);
            return *this;
        }

        friend self operator*(const self& lhs, const self& rhs) {
            auto rt = *lhs;
            rt.dot(rhs);
            return rt;
        }

        self& operator*=(const self& rhs) {
            (*this).dot(rhs);
            return *this;
        }
};

template <typename T>
struct dummy_derived {};

export {
    template <typename T, size_t pSize_>
    using vector = vector_base<dummy_derived, T, pSize_>;

    using vector2i = vector2<int>;
    using vector3i = vector3<int>;
    using vector4i = vector4<int>;

    using vector2f = vector2<float>;
    using vector3f = vector3<float>;
    using vector4f = vector4<float>;

    using vector2d = vector2<double>;
    using vector3d = vector3<double>;
    using vector4d = vector4<double>;
}

}  // namespace toy::algebra
