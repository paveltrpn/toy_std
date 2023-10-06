
#ifndef __array_h__
#define __array_h__

#include <stdexcept>

namespace toy {

template<typename T, int len>
struct array {
    array() = default;
    array(const array& rhs) = default;
    array(array && rhs) = default;

    array& operator=(const array& rhs) = default;
    array& operator=(array&& rhs) = default;

    ~array() = default;
    
    T& operator[](size_t id) {
        return _data[id];
    }

    T& at(size_t id) {
        if (id < len) {
            return _data[id];
        } else {
            throw std::invalid_argument{"array bounds violition"};
        }
    }

    private:
        T _data[len];
};

}

#endif
