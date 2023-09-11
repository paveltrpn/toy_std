
#ifndef __toy_vector_h__
#define __toy_vector_h__

#include <memory>

#include "common.h"

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

        ~vector() {
        }

        void push_back(T elem) {
            if (size_ == capacity_) {
                PRINTMSG("vector call realloc\n");

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

    private:
        size_t size_;
        size_t capacity_;

        std::unique_ptr<T[]> data_;
};
}  // namespace toy

#endif
