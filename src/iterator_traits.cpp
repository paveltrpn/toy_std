
module;

export module toy_std.iterator_traits;

namespace toy {

export struct input_iterator_tag {};

export struct output_iterator_tag {};

export struct forward_iterator_tag : public input_iterator_tag {};

export struct bidirectional_iterator_tag : public forward_iterator_tag {};

export struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// in gcc std lib this compiles only for c++17
export struct contiguous_iterator_tag : public random_access_iterator_tag {};

}  // namespace toy
