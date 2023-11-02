
#ifndef __toy_raw_vector_h__
#define __toy_raw_vector_h__

#include <iostream>
#include <format>
#include <type_traits>
#include <algorithm>
#include <string>

#define DEBUG

namespace toy {

template <typename T, typename = void>
class raw_vector {
        raw_vector() = default;
        raw_vector(raw_vector& other) = default;
        raw_vector(raw_vector&& other) = default;

        raw_vector& operator=(raw_vector& other) = default;
        raw_vector& operator=(raw_vector&& other) = default;
};

template <typename T>
// class raw_vector<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
struct raw_vector<
  T,
  typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, int>::value
                          || std::is_base_of<T, std::string>::value>::type> {
        /*
         * constructor with user-defined capacity
         * always create vector with size = 1
         */
        raw_vector(size_t c = 1) : capacity_{ c } {
            if (c < 1) {
                capacity_ = 1;
            }
            size_ = 0;
            data_ = new T[capacity_];
        };

        /*
         * constructor with user-defined size
         * and filled with default value
         */
        raw_vector(size_t s, T value) : size_{ s } {
            if (s >= 1) {
                capacity_ = size_;
                data_ = new T[capacity_];

                std::fill(data_, data_ + size_, value);
                return;
            }
            capacity_ = 1;
            data_ = new T[capacity_];
            data_[size_] = value;
#ifdef DEBUG
            std::cout << std::format("WARNING! raw_vector(size_t, T): with zero size!\n");
#endif
        }

        raw_vector(const raw_vector& rhs) {
            capacity_ = rhs.capacity_;
            size_ = rhs.size_;

            data_ = new T[capacity_];

            std::copy(rhs.data_, rhs.data_ + size_, data_);
        }

        raw_vector(raw_vector&& rhs) noexcept {
            capacity_ = rhs.capacity_;
            size_ = rhs.size_;

            data_ = rhs.data_;

            rhs.capacity_ = rhs.size_ = 0;
            rhs.data_ = nullptr;
        };

        raw_vector& operator=(const raw_vector& rhs) {
            if (this == &rhs) {
                return *this;
            }

            size_ = rhs.size_;
            capacity_ = rhs.capacity_;

            delete[] data_;

            data_ = new T[capacity_];

            std::copy(rhs.data_, rhs.data_ + size_, data_);

            return *this;
        }

        raw_vector& operator=(raw_vector&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            size_ = rhs.size_;
            capacity_ = rhs.capacity_;

            delete[] data_;
            data_ = rhs.data_;

            rhs.capacity_ = rhs.size_ = 0;
            rhs.data_ = nullptr;

            return *this;
        }

        ~raw_vector() {
            delete[] data_;
        }

        void push_back(T&& elem) {
            if (size_ == capacity_) {
#ifdef DEBUG
                std::cout << std::format("vector call realloc\n");
#endif
                capacity_ *= 2;

                T* nd = new T[capacity_];

                std::copy(data_, data_ + size_, nd);
                std::swap(nd, data_);

                delete[] nd;

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
        /*
         * Test purpose members
         */

        [[nodiscard]] constexpr size_t getSize() const {
            return size_;
        };

        [[nodiscard]] constexpr size_t getCap() const {
            return capacity_;
        };

        T* getPtr() const {
            return data_;
        }

    private:
        size_t size_;
        size_t capacity_;

        T* data_;
};

}  // namespace toy

#endif
