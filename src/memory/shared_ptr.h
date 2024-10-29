
#pragma once

#include "deleters.h"

namespace toy
{
template <typename T, typename D = __detail::default_delete_verbose<T>> struct shared_ptr final {
public:
    using element_type = T;
    using deleter_type = D;

private:
    element_type *_ptr;
};
} // namespace toy
