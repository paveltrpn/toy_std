
#ifndef __toy_vector_h__
#define __toy_vector_h__

#include <iostream>
#include <format>
#include <memory>

#define DEBUG

namespace toy {

template <typename T>
class vector {
    public:
        vector() {
            capacity_ = 1;
            size_ = 0;
            data_ = std::make_unique<T[]>(capacity_);
        };

        vector(size_t c) : capacity_{ c } {
            size_ = 0;
            data_ = std::make_unique<T[]>(capacity_);
        }

        vector(const vector& rhs) = default;
        vector(vector&& rhs) = default;

        vector& operator=(const vector& rhs) = default;
        vector& operator=(vector&& rhs) = default;

        ~vector() = default;

        void push_back(T elem) {
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

                auto old = nd.release();
                delete[] old;

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

        T& at(size_t id) {
            if (id < size_) {
                return data_[id];
            } else {
                throw std::invalid_argument{ "vector bounds violition" };
            }
        }

    private:
        size_t size_;
        size_t capacity_;

        std::unique_ptr<T[]> data_;
};

}  // namespace toy

#endif
