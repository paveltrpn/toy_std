
module;

#include <cstddef>

export module toy_stl.mvector;

import toy_stl.concepts;
import toy_stl.array;

export {
    namespace toy::math {

    template <toy::Arithmetical T, size_t size>
    struct vector;

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

    template <typename T>
    using vector2 = vector<T, 2>;

    template <typename T>
    using vector3 = vector<T, 3>;

    template <typename T>
    using vector4 = vector<T, 4>;

    }  // namespace toy::math
}
