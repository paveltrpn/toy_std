
module;

#include <type_traits>

export module toy_std.optional;

namespace toy {

struct nullopt_t {
    enum class secret_ { token_ };
    explicit constexpr nullopt_t( secret_ ) {}
};

constexpr nullopt_t nullopt{ nullopt_t::secret_::token_ };

/* An optional object is an object that contains the storage for another object and manages the
 * lifetime of this contained object, if any. The contained object may be initialized after the
 * optional object has been initialized, and may be destroyed before the optional object has been
 * destroyed. The initialization state of the contained object is tracked by the optional object.
 *
 * optional type must be conditionally trival destructible.
 */
template <typename Tp_>
struct optional {
    using value_type = Tp_;
    using reference = Tp_&;
    using pointer = Tp_*;

    // thank you, folly
    static_assert( !std::is_reference<value_type>::value,
                   "Optional may not be used with reference types" );
    static_assert( !std::is_abstract<value_type>::value,
                   "Optional may not be used with abstract types" );

    optional() noexcept
        : emptyState_{ 0 }
        , engaged_( false ) {}

    optional( const value_type& value ) noexcept
        : Tp_{ value }
        , engaged_( true ) {}

private:
    union {
        char emptyState_;
        value_type value_;
    };
    bool engaged_;
};

}  // namespace toy
