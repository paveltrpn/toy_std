
module;

#include <cstddef>
#include <algorithm>
#include <mdspan>

export module toy_std.algebra:matrix;

import toy_std.concepts;
import toy_std.array;

namespace toy::algebra {

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

constexpr size_t __SZ2 = 2;
constexpr size_t __SZ3 = 3;
constexpr size_t __SZ4 = 4;

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
            __matrix_sqr_mult(*this, b);
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
            __matrix_sqr_mult(*this, b);
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
            __matrix_sqr_mult(*this, b);
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

    private:
        toy::array<T, __SZ4 * __SZ4> data_;
};

template <typename T>
using matrix2 = matrix<T, __SZ2, __SZ2>;

template <typename T>
using matrix3 = matrix<T, __SZ3, __SZ3>;

template <typename T>
using matrix4 = matrix<T, __SZ4, __SZ4>;

export using matrix2f = matrix2<float>;
export using matrix3f = matrix3<float>;
export using matrix4f = matrix4<float>;

}  // namespace toy::algebra
