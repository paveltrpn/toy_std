
module;

#include <algorithm>
#include <iostream>
#include <format>
#include <memory>
#include <initializer_list>

// #define DEBUG

export module toy_std.vector;

import toy_std.concepts;
import toy_std.iterator_traits;

export {
    namespace toy {

    template <typename T>
    struct vector_iterator {
            using self = vector_iterator<T>;

            using range_type = T;
            using size_type = std::size_t;

            using value_type = typename range_type::value_type;
            using reference = value_type&;
            using pointer = value_type*;
            using const_reference = const value_type&;
            using const_pointer = const value_type*;
            using difference_type = std::size_t;
            using iterator_category = toy::contiguous_iterator_tag;

            vector_iterator() = default;
            explicit vector_iterator(range_type& range, size_type element)
                : element_{ element }, range_{ range } {};

            vector_iterator(const self& rhs) : element_{ rhs.element_ }, range_{ rhs.range_ } {};

            self& operator=(const self& rhs) {
                this->element_ = rhs.element_;
                this->range_ = rhs.range_;
                return *this;
            }

            reference operator*() {
                return range_[element_];
            };

            reference operator*() const {
                return range_[element_];
            };

            pointer operator->() {
                return &range_[element_];
            }

            pointer operator->() const {
                return &range_[element_];
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
                return std::abs(static_cast<long long>(rhs.element_)
                                - static_cast<long long>(element_));
            }

            reference operator[](size_type element) {
                return range_[element];
            }

            bool operator==(const self& rhs) const noexcept {
                return element_ == rhs.element_;
            };

            bool operator!=(const self& rhs) const noexcept {
                return !(*this == rhs);
            };

            bool operator<(const self& rhs) const noexcept {
                return range_[element_] < rhs.range_[rhs.element_];
            };

            bool operator>(const self& rhs) const noexcept {
                return !(*this < rhs) && !(this == rhs);
            };

            bool operator>=(const self& rhs) const noexcept {
                return !(*this < rhs);
            };

            bool operator<=(const self& rhs) const noexcept {
                return !(*this > rhs);
            };

            size_type element_;
            range_type& range_;
    };

    template <typename T>
    struct vector_const_iterator {
            using self = vector_const_iterator<T>;

            using range_type = T;
            using size_type = std::size_t;

            using value_type = typename range_type::value_type;
            using reference = value_type&;
            using pointer = value_type*;
            using const_reference = const value_type&;
            using const_pointer = const value_type*;
            using difference_type = std::size_t;
            using iterator_category = toy::contiguous_iterator_tag;

            vector_const_iterator() = default;
            explicit vector_const_iterator(range_type& range, size_type element)
                : element_{ element }, range_{ range } {};

            vector_const_iterator(const self& rhs)
                : element_{ rhs.element_ }, range_{ rhs.range_ } {};

            self& operator=(const self& rhs) {
                this->element_ = rhs.element_;
                this->range_ = rhs.range_;
                return *this;
            }

            const value_type& operator*() {
                return range_[element_];
            };

            const value_type& operator*() const {
                return range_[element_];
            };

            const pointer operator->() {
                return &range_[element_];
            }

            const pointer operator->() const {
                return &range_[element_];
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
                return std::abs(static_cast<long long>(rhs.element_)
                                - static_cast<long long>(element_));
            }

            reference operator[](size_type element) {
                return range_[element];
            }

            bool operator==(const self& rhs) const noexcept {
                return element_ == rhs.element_;
            };

            bool operator!=(const self& rhs) const noexcept {
                return !(*this == rhs);
            };

            bool operator<(const self& rhs) const noexcept {
                return range_[element_] < rhs.range_[rhs.element_];
            };

            bool operator>(const self& rhs) const noexcept {
                return !(*this < rhs) && !(this == rhs);
            };

            bool operator>=(const self& rhs) const noexcept {
                return !(*this < rhs);
            };

            bool operator<=(const self& rhs) const noexcept {
                return !(*this > rhs);
            };

            size_type element_;
            range_type& range_;
    };

    template <typename T>
    struct vector {
            using value_type = T;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type*;

            using iterator = vector_iterator<vector<T>>;
            using const_iterator = vector_const_iterator<T>;

            /*
             * constructor with user-defined capacity
             * always create vector with size = 1
             */
            explicit vector(size_t c = 1) : capacity_{ c } {
                if (c < 1) {
                    capacity_ = 1;
                }
                size_ = 0;
                data_ = std::make_unique<T[]>(capacity_);
            }

            /*
             * constructor with user-defined size
             * and filled with default value
             */
            vector(size_t s, T value) : size_{ s } {
                if (s >= 1) {
                    capacity_ = size_;
                    data_ = std::make_unique<T[]>(capacity_);

                    for (size_t i = 0; i < size_; ++i) {
                        data_[i] = value;
                    }
                    return;
                }
                capacity_ = 1;
                data_ = std::make_unique<T[]>(capacity_);
                data_[size_] = value;
#ifdef DEBUG
                std::cout << std::format("WARNING! vector(size_t, T): with zero size!\n");
#endif
            }

            explicit vector(std::initializer_list<T> list) {
                size_ = capacity_ = std::size(list);
                data_ = std::make_unique<T[]>(capacity_);

                for (size_t i = 0; auto&& elem : list) {
                    data_[i] = elem;
                    ++i;
                }
            }

            explicit vector(const vector& rhs) {
                capacity_ = rhs.capacity_;
                size_ = rhs.size_;

                data_ = std::make_unique<T[]>(capacity_);

                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = rhs.data_[i];
                }
            }

            vector(vector&& rhs) noexcept {
                capacity_ = rhs.capacity_;
                size_ = rhs.size_;

                data_ = std::move(rhs.data_);

                rhs.capacity_ = rhs.size_ = 0;
            };

            vector& operator=(const vector& rhs) {
                if (this != &rhs) {
                    size_ = rhs.size_;
                    capacity_ = rhs.capacity_;

                    data_.reset();
                    // Same as
                    // auto old = data_.release();
                    // delete[] old;

                    data_ = std::make_unique<T[]>(capacity_);

                    for (size_t i = 0; i < size_; ++i) {
                        data_[i] = rhs.data_[i];
                    }
                }

                return *this;
            }

            vector& operator=(vector&& rhs) noexcept {
                if (this != &rhs) {
                    capacity_ = rhs.capacity_;
                    size_ = rhs.size_;
                    data_ = std::move(rhs.data_);

                    rhs.capacity_ = rhs.size_ = 0;
                }

                return *this;
            }

            ~vector() = default;

            iterator begin() {
                return iterator{ *this, 0 };
            }

            iterator end() {
                return iterator{ *this, size_ };
            }

            const_iterator cbegin() {
                return const_iterator{ *this, 0 };
            }

            const_iterator cend() {
                return const_iterator{ *this, size_ };
            }

            void push_back(T&& elem) {
                if (size_ == capacity_) {
#ifdef DEBUG
                    std::cout << std::format("vector call realloc\n");
#endif
                    capacity_ *= 2;

                    auto nd = std::make_unique<T[]>(capacity_);

                    for (size_t i = 0; i < size_; ++i) {
                        nd[i] = data_[i];
                    }
                    data_.swap(nd);

                    nd.reset();
                    // Same as
                    // auto old = nd.release();
                    // delete[] old;

                    data_[size_] = elem;
                } else {
                    data_[size_] = elem;
                }
                size_++;
            }

            T pop_back() {
                auto elem = data_[size_ - 1];
                size_--;
                return elem;
            }

            T& operator[](size_t id) {
                return data_[id];
            }

            const T& operator[](size_t id) const {
                return data_[id];
            }

            T& at(size_t id) {
                if (id < size_) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "vector bounds violition" };
                }
            }

            const T& at(size_t id) const {
                if (id < size_) {
                    return data_[id];
                } else {
                    throw std::invalid_argument{ "vector bounds violition" };
                }
            }

            [[nodiscard]] constexpr size_t size() const {
                return size_;
            };

            [[nodiscard]] constexpr size_t capacity() const {
                return capacity_;
            };

            [[nodiscard]]
            T* data() const {
                return data_.get();
            }

        private:
            size_t size_{};
            size_t capacity_{};

            std::unique_ptr<T[]> data_{};
    };

    }  // namespace toy
}
