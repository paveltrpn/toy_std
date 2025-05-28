
module;

#include <functional>
#include <type_traits>

export module toy_std.memory:unique_ptr;

import :deleters;

namespace toy {

template <typename T>
struct is_deleter_function_candidate : std::false_type {};

template <typename T>
struct is_deleter_function_candidate<void ( * )( T * )> : std::true_type {};

template <typename T>
constexpr auto is_deleter_function_candidate_v =
    is_deleter_function_candidate<T>::value;

export template <typename T, typename D = default_delete_verbose<T>>
struct unique_ptr final
    : std::conditional_t<is_deleter_function_candidate_v<D>,
                         deleter_pointer_wrapper<T>, D> {
public:
    using element_type = T;
    using deleter_type = std::conditional_t<is_deleter_function_candidate_v<D>,
                                            deleter_pointer_wrapper<T>, D>;

    constexpr unique_ptr() noexcept
        : _ptr{ nullptr } {}

    unique_ptr( const unique_ptr & ) = delete;

    unique_ptr( nullptr_t ) noexcept
        : _ptr{ nullptr } {}

    unique_ptr( element_type *p ) noexcept
        : _ptr{ p } {};

    unique_ptr( element_type *p, void ( *pf )( element_type * ) ) noexcept
        : deleter_type{ pf }
        , _ptr{ p } {};

    unique_ptr( unique_ptr &&rhs ) noexcept
        : _ptr{ std::exchange( rhs._ptr, nullptr ) } {};

    ~unique_ptr() {
        // We are child of D - deleter type template parameter,
        // therefore we can cast ourselves to base class which have
        // a overloaded call operator.
        // Can be replaced with std::invoke?
        ( *static_cast<deleter_type *>( this ) )( _ptr );
    }

    void swap( unique_ptr &other ) noexcept {
        using std::swap;
        swap( _ptr, other._ptr );
    }

    unique_ptr &operator=( const unique_ptr & ) = delete;

    unique_ptr &operator=( unique_ptr &&rhs ) noexcept {
        //unique_ptr{ rhs }.swap( *this );

        if ( this == &rhs ) {
            return *this;
        }

        reset();
        swap( rhs );

        return *this;
    }

    element_type &operator*() const { return *_ptr; }

    element_type *operator->() const noexcept { return _ptr; }

    explicit operator bool() const noexcept { return _ptr != nullptr; }

    element_type *get() const noexcept { return _ptr; }

    element_type *release() noexcept { return std::exchange( _ptr, nullptr ); }

    void reset( element_type *other = nullptr ) {
        if ( _ptr == other ) return;
        element_type *tmp = std::exchange( _ptr, other );
        ( *static_cast<deleter_type *>( this ) )( tmp );
    }

private:
    element_type *_ptr;
};

}  // namespace toy
