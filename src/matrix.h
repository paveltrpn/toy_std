
#include "concepts.h"
#include "array.h"

namespace toy::math {

template <toy::Arithmetical T, size_t rows, size_t columnes>
    requires(rows > 0 && columnes > 0)
struct matrix {
        matrix() = default;

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
        size_t rows_{ 2 };
        size_t columnes_{ 2 };

        toy::array<T, 4> data_;
};

template <toy::Arithmetical T>
struct matrix<T, 3, 3> {
        matrix() = default;

        ~matrix() = default;

    private:
        size_t rows_{ 3 };
        size_t columnes_{ 3 };

        toy::array<T, 9> data_;
};

template <toy::Arithmetical T>
struct matrix<T, 4, 4> {
        matrix() = default;

        ~matrix() = default;

    private:
        size_t rows_{ 4 };
        size_t columnes_{ 4 };

        toy::array<T, 16> data_;
};

}  // namespace toy::math
