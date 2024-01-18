
module;

#include <cstddef>
#include <cmath>

export module toy_std.algebra:vector;

import toy_std.concepts;
import toy_std.array;

export {
    namespace toy::algebra {

    template <toy::Arithmetical T, size_t size>
    struct vector;

    template <toy::Arithmetical T>
    struct vector<T, 2> {
            using self = vector<T, 2>;
            using value_type = T;

            vector() = default;

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
            toy::array<T, 2> data_;
    };

    template <toy::Arithmetical T>
    struct vector<T, 3> {
            using self = vector<T, 3>;
            using value_type = T;

            vector() = default;

            vector(value_type x, value_type y, value_type z) {
                data_[0] = x;
                data_[1] = y;
                data_[2] = z;
            }

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
            
            void sum(self b) {
                data_[0] += b.data_[0];
                data_[1] += b.data_[1];
                data_[2] += b.data_[2];
            };

            void sub(self b) {
                data_[0] -= b.data_[0];
                data_[1] -= b.data_[1];
                data_[2] -= b.data_[2];
            };

            value_type dot(self b) {
                return data_[0] * b.data_[0] + data_[1] * b.data_[1] + data_[2] * b.data_[2];
            }
            
            value_type length() {
                return sqrt(dot(*this));
            }

        private:
            toy::array<T, 3> data_;
    };

    template <toy::Arithmetical T>
    struct vector<T, 4> {
            using self = vector<T, 4>;
            using value_type = T;

            vector() = default;

            vector(value_type x, value_type y, value_type z, value_type w) {
                data_[0] = x;
                data_[1] = y;
                data_[2] = z;
                data_[3] = w;
            }

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

            void sum(self b) {
                data_[0] += b.data_[0];
                data_[1] += b.data_[1];
                data_[2] += b.data_[2];
                data_[3] += b.data_[3];
            };

            void sub(self b) {
                data_[0] -= b.data_[0];
                data_[1] -= b.data_[1];
                data_[2] -= b.data_[2];
                data_[3] -= b.data_[3];
            };

            value_type dot(self b) {
                return data_[0] * b.data_[0] + data_[1] * b.data_[1] + data_[2] * b.data_[2]
                       + data_[3] * b.data_[3];
            }

        private:
            toy::array<T, 4> data_;
    };

    template <typename T>
    using vector2 = vector<T, 2>;

    template <typename T>
    using vector3 = vector<T, 3>;

    template <typename T>
    using vector4 = vector<T, 4>;

    using vector2f = vector<float, 2>;
    using vector3f = vector<float, 3>;
    using vector4f = vector<float, 4>;

    }  // namespace toy::algebra
}
