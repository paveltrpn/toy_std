
module;

#include <array>

export module toy_std.algebra:quaternion;

namespace toy::algebra {

template <typename T>
struct quaternion_base {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        quaternion_base() {
            data_[0] = value_type{};
            data_[1] = value_type{};
            data_[2] = value_type{};
            data_[3] = value_type{};
        }

        explicit quaternion_base(const quaternion_base& rhs) = default;

        explicit quaternion_base(const std::array<T, 4>& rhs) {
            data_[0] = rhs[0];
            data_[1] = rhs[1];
            data_[2] = rhs[2];
            data_[3] = rhs[3];
        }

        quaternion_base(value_type x, value_type y, value_type z, value_type w) {
            data_[0] = x;
            data_[1] = y;
            data_[2] = z;
            data_[3] = w;
        }

        reference operator[](size_t id) {
            return data_[id];
        }

        const_reference operator[](size_t id) const {
            return data_[id];
        }

        value_type x() const {
            return data_[0];
        }

        value_type y() const {
            return data_[1];
        }

        value_type z() const {
            return data_[2];
        }

        value_type w() const {
            return data_[3];
        }

        quaternion_base& operator=(const quaternion_base& rhs) {
            if (this != &rhs) {
                data_[0] = rhs.data_[0];
                data_[1] = rhs.data_[1];
                data_[2] = rhs.data_[2];
                data_[3] = rhs.data_[3];
            }

            return *this;
        };

        quaternion_base operator+(const quaternion_base& b) {
            return quaternion_base{
                data_[0] + b[0], data_[1] + b[1], data_[2] + b[2], data_[3] + b[3]
            };
        }

        quaternion_base operator+=(const quaternion_base& b) {
            return this + b;
        }

        quaternion_base operator-(const quaternion_base& b) {
            return quaternion_base{
                data_[0] - b[0], data_[1] - b[1], data_[2] - b[2], data_[3] - b[3]
            };
        }

        quaternion_base operator-=(const quaternion_base& b) {
            return this - b;
        }

        quaternion_base& operator=(quaternion_base&& rhs) = delete;

        ~quaternion_base() = default;

        [[nodiscard]] T* data() {
            return data_.data();
        };

        [[nodiscard]] const T* data() const {
            return data_.data();
        };

    private:
        std::array<T, 4> data_{};
};

export {
    using quaterniond = quaternion_base<double>;
}

}  // namespace toy::algebra
