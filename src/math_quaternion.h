
#include "concepts.h"
#include "array.h"

namespace toy::math {

template <toy::Arithmetical T>
struct quaternion {
        quaternion() = default;

        ~quaternion() = default;

    private:
        toy::array<T, 4> data_;
};

}  // namespace toy::math
