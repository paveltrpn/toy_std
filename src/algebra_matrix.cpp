
module;

#include <cstddef>
#include <algorithm>

export module toy_std.algebra:matrix;

import toy_std.concepts;
import toy_std.array;

export {
    namespace toy::algebra {

    template <toy::Arithmetical T, size_t rows, size_t columnes>
        requires(rows > 0 && columnes > 0)
    struct matrix {
            matrix() = default;

            matrix(const matrix &rhs) : rows_(rhs.rows_), columnes_(rhs.columnes_) {
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

    template <toy::Arithmetical T>
    struct matrix<T, 2, 2> {
            matrix() = default;

            ~matrix() = default;

        private:
            static constexpr inline size_t size_ = 4;

            toy::array<T, size_> data_;
    };

    template <toy::Arithmetical T>
    struct matrix<T, 3, 3> {
            matrix() = default;

            ~matrix() = default;

        private:
            static constexpr inline size_t size_ = 9;

            toy::array<T, size_> data_;
    };

    template <toy::Arithmetical T>
    struct matrix<T, 4, 4> {
            matrix() = default;

            ~matrix() = default;

        private:
            static constexpr inline size_t size_ = 16;

            toy::array<T, size_> data_;
    };

    template <typename T>
    using matrix2 = matrix<T, 2, 2>;

    template <typename T>
    using matrix3 = matrix<T, 3, 3>;

    template <typename T>
    using matrix4 = matrix<T, 4, 4>;

    using matrix2f = matrix<float, 2, 2>;
    using matrix3f = matrix<float, 3, 3>;
    using matrix4f = matrix<float, 4, 4>;

    }  // namespace toy::algebra
}
