
module;

#include <cstddef>
#include <algorithm>
#include <mdspan>
#include <numbers>

export module toy_std.algebra:matrix;

import toy_std.concepts;
import toy_std.array;
import :vector;

namespace toy::algebra {

template <typename T>
constexpr T degToRad(T deg) {
    return deg * M_PI / 180.0;
}

template <std::unsigned_integral T>
constexpr size_t idRw(T i, size_t j, T n) {
    return (i * n + j);
};

template <std::unsigned_integral T>
constexpr size_t idCw(T i, T j, T n) {
    return (j * n + i);
};

template <toy::Arithmetical T, size_t pWidth_, size_t pHeight_>
    requires(pWidth_ > 0 && pHeight_ > 0)
struct matrix;

template <toy::Arithmetical T, size_t pSize_>
void __matrix_sqr_set_idtt(matrix<T, pSize_, pSize_>& a) {
    for (size_t i = 0; i < pSize_; i++) {
        for (size_t j = 0; j < pSize_; j++) {
            if (i == j) {
                a[i, j] = static_cast<T>(1);
            } else {
                a[i, j] = T{};
            }
        }
    }
}

template <toy::Arithmetical T, size_t pSize_>
auto __matrix_sqr_mult(const matrix<T, pSize_, pSize_>& a, const matrix<T, pSize_, pSize_>& b) {
    matrix<T, pSize_, pSize_> rt;

    for (size_t i = 0; i < pSize_; i++) {
        for (size_t j = 0; j < pSize_; j++) {
            for (size_t k = 0; k < pSize_; k++) {
                rt[i, j] += a[k, j] * b[i, k];
            }
        }
    }

    return rt;
}

template <toy::Arithmetical T, size_t pWidth_, size_t pHeight_>
    requires(pWidth_ > 0 && pHeight_ > 0)
struct matrix {
        using self = matrix<T, pWidth_, pHeight_>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        matrix() = default;
        matrix(const self& rhs) = default;
        matrix(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~matrix() = default;

        template <typename U, size_t pSize_>
        friend void __matrix_sqr_set_idtt(matrix<U, pSize_, pSize_>& a);
        template <typename U, size_t pSize_>
        friend auto __matrix_sqr_mult(const matrix<U, pSize_, pSize_>& a,
                                      const matrix<U, pSize_, pSize_>& b);

        // row-wise indexing operator
        reference operator[](size_t i, size_t j) {
            return std::mdspan(data_.data(), pWidth_, pHeight_)[i, j];
        }

        void set_idtt() {
            __matrix_sqr_set_idtt(*this);
        }

        self mult(self b) {
            return __matrix_sqr_mult(*this, b);
        }

    private:
        toy::array<T, pWidth_ * pHeight_> data_;
};

template <toy::Arithmetical T>
struct matrix<T, __SZ2, __SZ2> {
        using self = matrix<T, __SZ2, __SZ2>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        matrix() = default;
        matrix(const self& rhs) = default;
        matrix(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~matrix() = default;

        template <typename U, size_t pSize_>
        friend void __matrix_sqr_set_idtt(matrix<U, pSize_, pSize_>& a);
        template <typename U, size_t pSize_>
        friend auto __matrix_sqr_mult(const matrix<U, pSize_, pSize_>& a,
                                      const matrix<U, pSize_, pSize_>& b);

        // row-wise indexing operator
        reference operator[](size_t i, size_t j) {
            return std::mdspan(data_.data(), __SZ2, __SZ2)[i, j];
        }

        void set_idtt() {
            __matrix_sqr_set_idtt(*this);
        }

        self mult(self b) {
            return __matrix_sqr_mult(*this, b);
        }

    private:
        toy::array<T, __SZ2 * __SZ2> data_;
};

template <toy::Arithmetical T>
struct matrix<T, __SZ3, __SZ3> {
        using self = matrix<T, __SZ3, __SZ3>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        matrix() = default;
        matrix(const self& rhs) = default;
        matrix(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~matrix() = default;

        template <typename U, size_t pSize_>
        friend void __matrix_sqr_set_idtt(matrix<U, pSize_, pSize_>& a);
        template <typename U, size_t pSize_>
        friend auto __matrix_sqr_mult(const matrix<U, pSize_, pSize_>& a,
                                      const matrix<U, pSize_, pSize_>& b);

        // row-wise indexing operator
        reference operator[](size_t i, size_t j) {
            return std::mdspan(data_.data(), __SZ3, __SZ3)[i, j];
        }

        void set_idtt() {
            __matrix_sqr_set_idtt(*this);
        }

        self mult(self b) {
            return __matrix_sqr_mult(*this, b);
        }

    private:
        toy::array<T, __SZ3 * __SZ3> data_;
};

template <toy::Arithmetical T>
struct matrix<T, __SZ4, __SZ4> {
        using self = matrix<T, __SZ4, __SZ4>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        matrix() = default;
        matrix(const self& rhs) = default;
        matrix(self&& rhs) = default;

        self& operator=(const self& rhs) = default;
        self& operator=(self&& rhs) = default;

        ~matrix() = default;

        template <typename U, size_t pSize_>
        friend void __matrix_sqr_set_idtt(matrix<U, pSize_, pSize_>& a);
        template <typename U, size_t pSize_>
        friend auto __matrix_sqr_mult(const matrix<U, pSize_, pSize_>& a,
                                      const matrix<U, pSize_, pSize_>& b);

        reference operator[](size_t id) const {
            return data_[id];
        }

        // row-wise indexing operator
        reference operator[](size_t i, size_t j) {
            return std::mdspan(data_.data(), __SZ4, __SZ4)[i, j];
        }

        const T& operator[](size_t i, size_t j) const {
            return std::mdspan(data_.data(), __SZ4, __SZ4)[i, j];
        }

        void set_idtt() {
            __matrix_sqr_set_idtt(*this);
        }

        self mult(self b) {
            __matrix_sqr_mult(*this, b);
        }
    
        self operator*(self& rhs) {
            *this = mult(rhs);
            return this;
        }

        void set_perspective(value_type fovy, value_type aspect, value_type near, value_type far) {
            value_type f = 1.0 / tanf(fovy / std::numbers::sqrt2_v<float>);
            value_type nf;

            data_[0] = f / aspect;
            data_[1] = 0.0;
            data_[2] = 0.0;
            data_[3] = 0.0;
            data_[4] = 0.0;
            data_[5] = f;
            data_[6] = 0.0;
            data_[7] = 0.0;
            data_[8] = 0.0;
            data_[9] = 0.0;
            data_[11] = -1.0;
            data_[12] = 0.0;
            data_[13] = 0.0;
            data_[15] = 0.0;

            if (far >= std::numeric_limits<float>::epsilon()) {
                nf = 1.0 / (near - far);
                data_[10] = (far + near) * nf;
                data_[14] = 2.0 * far * near * nf;
            } else {
                data_[10] = -1.0;
                data_[14] = -2.0 * near;
            }
        }

        void set_offset(const toy::algebra::vector4<value_type>& offset) {
            this->set_idtt();

            data_[0] = offset[0];
            data_[5] = offset[1];
            data_[11] = offset[2];
        }

        void transpose_self() {
            self tmp;

            tmp[0] = data_[0];
            tmp[1] = data_[4];
            tmp[2] = data_[8];
            tmp[3] = data_[12];
            tmp[4] = data_[1];
            tmp[5] = data_[5];
            tmp[6] = data_[9];
            tmp[7] = data_[13];
            tmp[8] = data_[2];
            tmp[9] = data_[6];
            tmp[10] = data_[10];
            tmp[11] = data_[14];
            tmp[12] = data_[3];
            tmp[13] = data_[7];
            tmp[14] = data_[11];
            tmp[15] = data_[15];

            *this = tmp;
        }

        void set_rotation_yaw(value_type angl) {
            this->set_idtt();
            value_type sa, ca;

            sincosf(degToRad(angl), &sa, &ca);

            data_[5] = ca;
            data_[6] = -sa;
            data_[9] = sa;
            data_[10] = ca;
        }

        void set_rotation_pith(value_type angl) {
            this->set_idtt();
            float sa, ca;

            sincosf(degToRad(angl), &sa, &ca);

            data_[0] = ca;
            data_[2] = sa;
            data_[8] = -sa;
            data_[10] = ca;
        }

        void set_rotation_roll(value_type angl) {
            this->set_idtt();
            float sa, ca;

            sincosf(degToRad(angl), &sa, &ca);

            data_[0] = ca;
            data_[1] = -sa;
            data_[4] = sa;
            data_[5] = ca;
        }

        void set_euler(value_type yaw, value_type pitch, value_type roll) {
            self y, p, r;

            y.set_rotation_yaw(yaw);
            p.set_rotation_pith(pitch);
            r.set_rotation_roll(roll);

            *this = y.mult(p);
            *this = this->mult(r);
        }

    private:
        toy::array<T, __SZ4 * __SZ4> data_;
};

export {
template <typename T>
using matrix2 = matrix<T, __SZ2, __SZ2>;

template <typename T>
using matrix3 = matrix<T, __SZ3, __SZ3>;

template <typename T>
using matrix4 = matrix<T, __SZ4, __SZ4>;

using matrix2f = matrix2<float>;
using matrix3f = matrix3<float>;
using matrix4f = matrix4<float>;

using matrix2d = matrix2<double>;
using matrix3d = matrix3<double>;
using matrix4d = matrix4<double>;
}

}  // namespace toy::algebra
