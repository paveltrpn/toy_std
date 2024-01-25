
module;

#include <cstddef>
#include <cmath>

export module toy_std.algebra:vector;

import toy_std.concepts;
import toy_std.array;

namespace toy::algebra {

static constexpr size_t __SZ2 = 2;
static constexpr size_t __SZ3 = 3;
static constexpr size_t __SZ4 = 4;

template <toy::Arithmetical T, size_t pSize_>
struct vector_base {
        using self = vector_base<T, pSize_>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        vector_base() = default;
        vector_base(const self& rhs) = default;
        vector_base(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;
};

template <toy::Arithmetical T, size_t size>
struct vector;

export {
    template <typename T>
    using vector2 = vector<T, __SZ2>;

    template <typename T>
    using vector3 = vector<T, __SZ3>;

    template <typename T>
    using vector4 = vector<T, __SZ4>;

    using vector2f = vector2<float>;
    using vector3f = vector3<float>;
    using vector4f = vector4<float>;

    using vector2d = vector2<double>;
    using vector3d = vector3<double>;
    using vector4d = vector4<double>;
}

template <toy::Arithmetical T>
struct vector<T, __SZ2> {
        using self = vector<T, __SZ2>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        vector() = default;
        vector(const self& rhs) = default;
        vector(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        vector(value_type x, value_type y) {
            data_[0] = x;
            data_[1] = y;
        }

        ~vector() = default;

        [[nodiscard]] value_type x() const {
            return data_[0];
        }

        [[nodiscard]] value_type y() const {
            return data_[1];
        }

        void sum(self b) {
            data_[0] += b.data_[0];
            data_[1] += b.data_[1];
        };

        void sub(self b) {
            data_[0] -= b.data_[0];
            data_[1] -= b.data_[1];
        };

        value_type dot(self b) {
            return data_[0] * b.data_[0] + data_[1] * b.data_[1];
        }

    private:
        toy::array<T, __SZ2> data_;
};

// vector3
template <toy::Arithmetical T>
struct vector<T, __SZ3> {
        using self = vector<T, __SZ3>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        vector() = default;
        vector(const self& rhs) = default;
        vector(self&& rhs) = default;

        vector(value_type x, value_type y, value_type z) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~vector() = default;

        value_type& operator[](size_t id) {
            return data_[id];
        }

        const value_type& operator[](size_t id) const {
            return data_[id];
        }

        [[nodiscard]] value_type x() const {
            return data_[0];
        }

        [[nodiscard]] value_type y() const {
            return data_[1];
        }

        [[nodiscard]] value_type z() const {
            return data_[2];
        }

        void sum_self(const self& b) {
            data_[0] += b.data_[0];
            data_[1] += b.data_[1];
            data_[2] += b.data_[2];
        };

        void sub_self(const self& b) {
            data_[0] -= b.data_[0];
            data_[1] -= b.data_[1];
            data_[2] -= b.data_[2];
        };

        value_type sum(const self& b) {
            return { data_[0] + b.data_[0], data_[1] + b.data_[1], data_[2] + b.data_[2] };
        };

        value_type sub(const self& b) {
            return { data_[0] - b.data_[0], data_[1] - b.data_[1], data_[2] - b.data_[2] };
        };

        value_type dot(self b) {
            return data_[0] * b.data_[0] + data_[1] * b.data_[1] + data_[2] * b.data_[2];
        }

        self scale(const self& v, float scale) {
            self rt;

            rt[0] = v[0] * scale;
            rt[1] = v[1] * scale;
            rt[2] = v[2] * scale;

            return rt;
        }

        void scale_self(float scale) {
            *this = scale(*this, scale);
        }

        self cross(self b) {
            return { data_[1] * b[2] - data_[2] * b[1],
                     data_[2] * b[0] - data_[0] * b[2],
                     data_[0] * b[1] - data_[1] * b[0] };
        }

        void cross_self(self b) {
            *this = cross(b);
        }

        value_type length() {
            return sqrt(dot(*this));
        }

    private:
        toy::array<T, __SZ3> data_;
};

template <toy::Arithmetical T>
struct vector<T, __SZ4> {
        using self = vector<T, __SZ4>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        vector() = default;
        vector(const self& rhs) = default;
        vector(self&& rhs) = default;

        vector(value_type x, value_type y, value_type z, value_type w) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
            data_[3] = w;
        }

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~vector() = default;

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

        void sum_self(const self& b) {
            data_[0] += b.data_[0];
            data_[1] += b.data_[1];
            data_[2] += b.data_[2];
            data_[3] += b.data_[3];
        };

        void sub_self(const self& b) {
            data_[0] -= b.data_[0];
            data_[1] -= b.data_[1];
            data_[2] -= b.data_[2];
            data_[3] -= b.data_[3];
        };

        value_type sum(const self& b) {
            return { data_[0] + b.data_[0],
                     data_[1] + b.data_[1],
                     data_[2] + b.data_[2],
                     data_[3] + b.data_[3] };
        };

        value_type sub(const self& b) {
            return { data_[0] - b.data_[0],
                     data_[1] - b.data_[1],
                     data_[2] - b.data_[2],
                     data_[3] - b.data_[3] };
        };

        value_type dot(self b) {
            return data_[0] * b.data_[0] + data_[1] * b.data_[1] + data_[2] * b.data_[2]
                   + data_[3] * b.data_[3];
        }

        self scale(const self& v, float scale) {
            self rt;

            rt[0] = v[0] * scale;
            rt[1] = v[1] * scale;
            rt[2] = v[2] * scale;
            rt[3] = v[3] * scale;

            return rt;
        }

        void scale_self(float scale) {
            *this = scale(*this, scale);
        }

    private:
        toy::array<T, __SZ4> data_;
};

}  // namespace toy::algebra
