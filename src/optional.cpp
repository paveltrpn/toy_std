
module;

export module toy_std.optional;

namespace toy {

export template <typename T>
struct optional {
        union {
                char dummy_;
                T value_;
        };
        bool engaged_;
};

}  // namespace toy
