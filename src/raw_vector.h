
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
class raw_vector<
  T,
  typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, int>::value
                          || std::is_base_of<T, std::string>::value>::type> {
    public:
        raw_vector() {
            capacity_ = 1;
            size_ = 0;
            data_ = new T[capacity_];
        };

        raw_vector(size_t c) : capacity_{ c } {
            size_ = 0;
            data_ = new T[capacity_];
        };

        raw_vector(raw_vector& other) = delete;
        raw_vector(raw_vector&& other) = delete;

        raw_vector& operator=(raw_vector& other) = delete;
        raw_vector& operator=(raw_vector&& other) = delete;

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
                size_ += 1;
            } else {
                data_[size_] = elem;
                size_ += 1;
            }
        }

        T& operator[](size_t id) {
            return data_[id];
        }

    private:
        size_t size_;
        size_t capacity_;

        T* data_;
};

}  // namespace toy

#endif
