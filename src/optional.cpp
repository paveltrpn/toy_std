
module;

#include <type_traits>

export module toy_std.optional;

namespace toy {

export struct nullopt_t {
        enum class secret_ { token_ };
        explicit constexpr nullopt_t(secret_) {
        }
};

constexpr nullopt_t nullopt{ nullopt_t::secret_::token_ };

// optional manage thier underlying object lifetime
// optional type must be conditionally trival destructible
export template <typename Tp_>
struct optional {
        using value_type = Tp_;
        using refeerence = Tp_&;
        using pointer = Tp_*;

        // thank you, folly
        static_assert(!std::is_reference<value_type>::value,
                      "Optional may not be used with reference types");
        static_assert(!std::is_abstract<value_type>::value,
                      "Optional may not be used with abstract types");

        optional() : emptyState_{ 0 }, engaged_(false) {
        }

        optional(const value_type& value) : Tp_{ value }, engaged_(true) {
        }

    private:
        union {
                char emptyState_;
                value_type value_;
        };
        bool engaged_;
};

}  // namespace toy
