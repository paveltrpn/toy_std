
#ifndef __stack_h__
#define __stack_h__

#include <iostream>

namespace toy {

template <typename T, template <typename> typename Cont, size_t depth = 16>
struct stack {
        stack(size_t d) : depth_{ d } {};
        
    private:
        Cont<T> container_;

        size_t depth_;
};

}  // namespace toy

#endif
