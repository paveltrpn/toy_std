
module;

#include <stdexcept>
#include <algorithm>

export module toy_std.array;

export {
    namespace toy {

    template <typename T, size_t len>
        requires(len > 0)
    struct array {
            using value_type = T;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type*;

            array() = default;

            explicit array(const array& rhs) {
                std::copy(std::begin(rhs.data_), std::end(rhs.data_), data_);
            }

            explicit array(T rhs[len]) {
                std::copy(rhs[0], rhs[len], data_);
            }

            /*
             * move constructor deleted because use static size array
             */
            array(array&& rhs) = delete;

            explicit array(T value) {
                for (size_t i = 0; i < len; ++i) {
                    data_[i] = value;
                }
            }

            explicit array(std::initializer_list<T> list) {
                for (size_t i = 0; auto&& elem : list) {
                    data_[i] = elem;
                    if (i > len)
                        break;
                    ++i;
                }
            }

            /*
             * copy assignment
             */
            array& operator=(const array& rhs) {
                if ((this != &rhs)) {
                    std::copy(std::begin(rhs.data_), std::end(rhs.data_), data_);
                }
                return *this;
            }

            array& operator=(T rhs[len]) {
                std::copy(rhs[0], rhs[len], data_);
            }

            /*
             * move assingment operator deleted because use static size array
             */
            array& operator=(array&& rhs) = delete;

            ~array() = default;

            reference operator[](size_t id) {
                return data_[id];
            }

            const_reference operator[](size_t id) const {
                return data_[id];
            }

            T& at(size_t id) {
                if (id < len) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "array bounds violition" };
                }
            }

            const T& at(size_t id) const {
                if (id < len) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "array bounds violition" };
                }
            }

            [[nodiscard]] pointer data() {
                return static_cast<pointer>(data_);
            }

            [[nodiscard]] const_pointer data() const {
                return static_cast<const_pointer>(data_);
            }

        private:
            value_type data_[len]{};
    };

    }  // namespace toy
}
