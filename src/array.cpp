
module;

#include <stdexcept>
#include <algorithm>

export module toy_std.array;

import toy_std.iterator_traits;

export {
    namespace toy {

    template <typename T>
    struct array_iterator {
            using self = array_iterator<T>;

            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using const_reference = const T&;
            using const_pointer = const T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = toy::contiguous_iterator_tag;

            array_iterator() = default;
            explicit array_iterator(pointer ptr) : element_{ ptr } {};

            reference operator*() const {
                return *element_;
            };

            pointer operator->() const {
                return element_;
            }

            // pre-increment
            reference operator++() {
                element_ += 1;
                return *element_;
            }

            // post-increment
            value_type operator++(int) {
                auto tmp{ *this };
                ++(*this);
                return tmp;
            }

            // pre-decrement
            reference operator--() {
                element_ -= 1;
                return *element_;
            }

            // post-decrement
            value_type operator--(int) {
                auto tmp{ *this };
                --(*this);
                return tmp;
            }

            friend bool operator==(const self& a, const self& b) {
                return a.element_ == b.element_;
            };

            friend bool operator!=(const self& a, const self& b) {
                return !(a == b);
            };

            pointer element_;
    };

    template <typename T>
    struct array_const_iterator {
            using self = array_const_iterator<T>;

            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using const_reference = const T&;
            using const_pointer = const T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = toy::contiguous_iterator_tag;

            array_const_iterator() = default;
            explicit array_const_iterator(pointer ptr) : element_{ ptr } {};

            const_reference operator*() const {
                return *element_;
            };

            const_pointer operator->() const {
                return element_;
            }

            // pre-increment
            const_reference operator++() {
                element_ += 1;
                return *element_;
            }

            // post-increment
            value_type operator++(int) {
                auto tmp{ *this };
                ++(*this);
                return tmp;
            }

            // pre-decrement
            const_reference operator--() {
                element_ -= 1;
                return *element_;
            }

            // post-decrement
            value_type operator--(int) {
                auto tmp{ *this };
                --(*this);
                return tmp;
            }

            friend bool operator==(const self& a, const self& b) {
                return a.element_ == b.element_;
            };

            friend bool operator!=(const self& a, const self& b) {
                return !(a == b);
            };

            pointer element_;
    };

    template <typename T, size_t len>
        requires(len > 0)
    struct array {
            using value_type = T;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type*;

            using iterator = array_iterator<T>;
            using const_iterator = array_const_iterator<T>;

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

            iterator begin() {
                return iterator{ &data_[0] };
            }

            iterator end() {
                return iterator{ &data_[len] };
            }

            const_iterator cbegin() {
                return const_iterator{ &data_[0] };
            }

            const_iterator cend() {
                return const_iterator{ &data_[len] };
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
