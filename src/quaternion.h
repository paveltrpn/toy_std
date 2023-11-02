
#include "concepts.h"
#include "array.h"
#include "mvector.h"

namespace toy::math {

template <toy::Arithmetical T>
struct quaternion {
        quaternion() = default;

        quaternion(quaternion&& rhs) = delete;

        quaternion(const quaternion& rhs) : data_{ rhs } {
        }

        quaternion(T x, T y, T z, T w) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
            data_[3] = w;
        }

        quaternion(const toy::math::vector2<T>& rhs) {
            data_[0] = rhs.data_[0];
            data_[1] = rhs.data_[1];
            data_[2] = data_[3] = T{};
        }

        quaternion(const toy::math::vector3<T>& rhs) {
            data_[0] = rhs.data_[0];
            data_[1] = rhs.data_[1];
            data_[2] = rhs.data_[2];
            data_[3] = T{};
        }

        quaternion(const toy::math::vector4<T>& rhs) {
            data_[0] = rhs.data_[0];
            data_[1] = rhs.data_[1];
            data_[2] = rhs.data_[2];
            data_[3] = rhs.data_[3];
        }

        T operator[](size_t id) {
            return data_[id];
        }

        const T operator[](size_t id) const {
            return data_[id];
        }

        quaternion& operator=(const quaternion& rhs) {
            if (&rhs != this) {
                data_ = rhs.data_;
            }

            return *this;
        }

        quaternion& operator+(const quaternion& b) {
            return quaternion{ data_[0] + b[0], data_[1] + b[1], data_[2] + b[2], data_[3] + b[3] };
        }

        quaternion& operator+=(const quaternion& b) {
            return this + b;
        }

        quaternion& operator-(const quaternion& b) {
            return quaternion{ data_[0] + b[0], data_[1] + b[1], data_[2] + b[2], data_[3] + b[3] };
        }

        quaternion& operator-=(const quaternion& b) {
            return this - b;
        }

        quaternion& operator=(quaternion&& rhs) = delete;

        ~quaternion() = default;

    private:
        toy::array<T, 4> data_;
};

}  // namespace toy::math
