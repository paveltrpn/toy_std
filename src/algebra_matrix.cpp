
module;

#include <cstddef>
#include <algorithm>
#include <mdspan>

export module toy_std.algebra:matrix;

import toy_std.concepts;
import toy_std.array;

template <std::unsigned_integral T>
constexpr size_t idRw(T i, size_t j, T n) {
    return (i * n + j);
};

template <std::unsigned_integral T>
constexpr size_t idCw(T i, T j, T n) {
    return (j * n + i);
};

export {
    namespace toy::algebra {

    template <toy::Arithmetical T, size_t rows, size_t columnes>
        requires(rows > 0 && columnes > 0)
    struct matrix {
            matrix() = default;

            matrix(const matrix& rhs) : rows_(rhs.rows_), columnes_(rhs.columnes_) {
                for (size_t i = 0; i < rows_; ++i) {
                    std::copy(rhs.data_[i], rhs.data_[i] + columnes_, data_[i]);
                }
            };

            ~matrix() = default;

        private:
            size_t rows_{ rows };
            size_t columnes_{ columnes };

            toy::array<T, rows * columnes> data_;
    };

    template <toy::Arithmetical T, size_t size_>
        requires(size_ > 0)
    struct matrix_sqr {
            using self = matrix_sqr<T, size_>;
            using value_type = T;
            using reference = T&;
            using pointer = T*;

            matrix_sqr() = default;
            matrix_sqr(const self& rhs) = default;
            matrix_sqr(self&& rhs) = default;

            self& operator=(const self& rhs) = default;
            self& operator=(self&& rhs) = default;

            ~matrix_sqr() = default;

            // row-wise indexing operator
            reference operator[](size_t i, size_t j) {
                auto span = std::mdspan(data_.data(), size_, size_);
                return span[i, j];
            }

            void set_idtt() {
                auto span = std::mdspan(data_.data(), size_, size_);
                for (size_t i = 0; i < size_; i++) {
                    for (size_t j = 0; j < size_; j++) {
                        if (i == j) {
                            span[i, j] = static_cast<value_type>(1);
                        } else {
                            span[i, j] = value_type{};
                        }
                    }
                }
            }

            self mult(self b) {
                self rt{ value_type{} };

                for (size_t i = 0; i < size_; i++) {
                    for (size_t j = 0; j < size_; j++) {
                        for (size_t k = 0; k < size_; k++) {
                            rt[i, j] += *this[k, j] * b[i, k];
                        }
                    }
                }

                return rt;
            }

        private:
            toy::array<T, size_ * size_> data_;
    };

    template <typename T>
    using matrix2 = matrix_sqr<T, 2>;

    template <typename T>
    using matrix3 = matrix_sqr<T, 3>;

    template <typename T>
    using matrix4 = matrix_sqr<T, 4>;

    using matrix2f = matrix2<float>;
    using matrix3f = matrix3<float>;
    using matrix4f = matrix4<float>;

    }  // namespace toy::algebra
}
