
#include "concepts.h"

namespace toy {

template <toy::Arithmetical T>
struct matrix {
        matrix() : rows_{}, columnes_{}, data_{} {
        }

        matrix(size_t size) : rows_{ size }, columnes_{ size } {
            data_ = new T[rows_ * columnes_];
        }

        matrix(size_t rows, size_t columnes) : rows_{ rows }, columnes_{ columnes } {
            data_ = new T[rows_ * columnes_];
        }

        ~matrix() {
            delete[] data_;
        }

    private:
        size_t rows_;
        size_t columnes_;

        T data_[];
};

}  // namespace toy
