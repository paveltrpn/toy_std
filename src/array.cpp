
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

            reference operator*() {
                return *element_;
            };

            reference operator*() const {
                return *element_;
            };

            pointer operator->() {
                return element_;
            }

            pointer operator->() const {
                return element_;
            }

            // pre-increment
            self& operator++() {
                ++element_;
                return *this;
            }

            // post-increment
            self operator++(int) {
                auto tmp{ this };
                ++this;
                return tmp;
            }

            // pre-decrement
            self& operator--() {
                --element_;
                return *this;
            }

            // post-decrement
            self operator--(int) {
                auto tmp{ this };
                --this;
                return tmp;
            }

            self& operator+=(difference_type offst) {
                element_ = element_ + offst;
                return *this;
            }

            self& operator-=(difference_type offst) {
                element_ = element_ - offst;
                return *this;
            }

            self operator+(difference_type offst) {
                auto tmp{ *this };
                tmp += offst;
                return tmp;
            }

            self operator-(difference_type offst) {
                auto tmp{ *this };
                tmp -= offst;
                return tmp;
            }

            self operator+(difference_type offst) const {
                auto tmp{ *this };
                tmp += offst;
                return tmp;
            }

            self operator-(difference_type offst) const {
                auto tmp{ *this };
                tmp -= offst;
                return tmp;
            }

            difference_type operator-(self rhs) const {
                return rhs.element_ - element_;
            }

            bool operator==(const self& rhs) const {
                return element_ == rhs.element_;
            };

            bool operator!=(const self& rhs) {
                return !(*this == rhs);
            };

            friend bool operator>(const self& a, const self& b) {
                return *a.element_ > *b.element_;
            };

            friend bool operator<(const self& a, const self& b) {
                return *a.element_ < *b.element_;
            };

            friend bool operator<=(const self& a, const self& b) {
                return *a.element_ <= *b.element_;
            };

            friend bool operator>=(const self& a, const self& b) {
                return *a.element_ >= *b.element_;
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

            const_reference operator*() {
                return *element_;
            };

            const_reference operator*() const {
                return *element_;
            };

            const_pointer operator->() {
                return element_;
            }

            const_pointer operator->() const {
                return element_;
            }

            // pre-increment
            self& operator++() {
                ++element_;
                return *this;
            }

            // post-increment
            self operator++(int) {
                auto tmp{ this };
                ++this;
                return tmp;
            }

            // pre-decrement
            self& operator--() {
                --element_;
                return *this;
            }

            // post-decrement
            self operator--(int) {
                auto tmp{ this };
                --this;
                return tmp;
            }

            self& operator+=(difference_type offst) {
                element_ = element_ + offst;
                return *this;
            }

            self& operator-=(difference_type offst) {
                element_ = element_ - offst;
                return *this;
            }

            self operator+(difference_type offst) {
                auto tmp{ *this };
                tmp += offst;
                return tmp;
            }

            self operator-(difference_type offst) {
                auto tmp{ *this };
                tmp -= offst;
                return tmp;
            }

            self operator+(difference_type offst) const {
                auto tmp{ *this };
                tmp += offst;
                return tmp;
            }

            self operator-(difference_type offst) const {
                auto tmp{ *this };
                tmp -= offst;
                return tmp;
            }

            difference_type operator-(self rhs) const {
                return rhs.element_ - element_;
            }

            bool operator==(const self& rhs) const {
                return element_ == rhs.element_;
            };

            bool operator!=(const self& rhs) {
                return !(*this == rhs);
            };

            friend bool operator>(const self& a, const self& b) {
                return *a.element_ > *b.element_;
            };

            friend bool operator<(const self& a, const self& b) {
                return *a.element_ < *b.element_;
            };

            friend bool operator<=(const self& a, const self& b) {
                return *a.element_ <= *b.element_;
            };

            friend bool operator>=(const self& a, const self& b) {
                return *a.element_ >= *b.element_;
            };
            pointer element_;
    };

    template <typename T, size_t size_>
        requires(size_ > 0)
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

            explicit array(T rhs[size_]) {
                std::copy(rhs[0], rhs[size_], data_);
            }

            /*
             * move constructor deleted because use static size array
             */
            array(array&& rhs) = delete;

            explicit array(T value) {
                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = value;
                }
            }

            explicit array(std::initializer_list<T> list) {
                for (size_t i = 0; auto&& elem : list) {
                    data_[i] = elem;
                    if (i > size_)
                        break;
                    ++i;
                }
            }

            iterator begin() {
                return iterator{ data() };
            }

            iterator end() {
                return iterator{ data() + size_ };
            }

            const_iterator cbegin() {
                return const_iterator{ data() };
            }

            const_iterator cend() {
                return const_iterator{ data() + size_ };
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

            array& operator=(T rhs[size_]) {
                std::copy(rhs[0], rhs[size_], data_);
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
                if (id < size_) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "array bounds violition" };
                }
            }

            const T& at(size_t id) const {
                if (id < size_) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "array bounds violition" };
                }
            }

            reference front() {
                return data_[0];
            }

            const_reference front() const {
                return data_[0];
            }

            reference back() {
                return data_[size_ - 1];
            }

            const_reference back() const {
                return data_[size_ - 1];
            }

            [[nodiscard]]
            size_t size() const {
                return size_;
            }

            [[nodiscard]]
            bool empty() const {
                return size_ == 0;
            }

            [[nodiscard]] pointer data() {
                return static_cast<pointer>(data_);
            }

            [[nodiscard]] const_pointer data() const {
                return static_cast<const_pointer>(data_);
            }

            void fill(const value_type& value) {
                for (auto& elem : *this) {
                    elem = value;
                }
            }

        private:
            value_type data_[size_]{};
    };

    }  // namespace toy
}
