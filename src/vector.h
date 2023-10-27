
#ifndef __toy_vector_h__
#define __toy_vector_h__

#include <algorithm>
#include <iostream>
#include <format>
#include <memory>

#define DEBUG

namespace toy {

template <typename T>
class vector {
    public:
        /*
         * constructor with user-defined capacity
         * always create vector with size = 1
         */
        vector(size_t c = 1) : capacity_{ c } {
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

        vector(const vector& rhs) {
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
            if (this == &rhs) {
                return *this;
            }

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

            return *this;
        }

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

        T& at(size_t id) {
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
            return data_.get();
        }

    private:
        size_t size_;
        size_t capacity_;

        std::unique_ptr<T[]> data_;
};

}  // namespace toy

#endif
