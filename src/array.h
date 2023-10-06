
#ifndef __array_h__
#define __array_h__

#include <stdexcept>

namespace toy {

template<typename T, size_t len>
struct array {
    array() = default;
    array(const array& rhs) = default;
    array(array && rhs) = default;
    
    array(T value) {
        for (size_t i = 0; i < len; ++i) {
            _data_[i] = value;
        }
    }

    array& operator=(const array& rhs) = default;
    array& operator=(array&& rhs) = default;

    ~array() = default;
    
    T& operator[](size_t id) {
        return data_[id];
    }

    T& at(size_t id) {
        if (id < len) {
            return data_[id];
        } else {
            throw std::invalid_argument{"array bounds violition"};
        }
    }

    private:
        T data_[len];
};

}

#endif
