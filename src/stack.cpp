
module;

#include <type_traits>
#include <cstddef>

export module toy_std.stack;

import toy_std.vector;
import toy_std.array;

export {
    namespace toy {

    template <typename T, template <typename> typename Cont, size_t depth = 16>
        requires std::is_same_v<Cont<T>, toy::vector<T>>
                 || std::is_same_v<Cont<T>, toy::array<T, depth>>
    struct stack {
            stack(size_t d) : depth_{ d } {};

        private:
            Cont<T> container_;

            size_t depth_{ depth };
    };

    }  // namespace toy
}
