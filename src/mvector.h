
#include "concepts.h"
#include "array.h"

namespace toy::math {

template <toy::Arithmetical T, size_t size> struct vector;

template <toy::Arithmetical T>
struct vector<T, 2> {
        vector() = default;

        ~vector() = default;

    private:
        toy::array<T, 2> data_;
};

template <toy::Arithmetical T>
struct vector<T, 3> {
        vector() = default;

        ~vector() = default;

    private:
        toy::array<T, 3> data_;
};

template <toy::Arithmetical T>
struct vector<T, 4> {
        vector() = default;

        ~vector() = default;

    private:
        toy::array<T, 4> data_;
};

}  // namespace toy::math
