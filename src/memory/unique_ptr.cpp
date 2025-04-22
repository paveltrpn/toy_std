
module;

#include <functional>

export module toy_std.memory:unique_ptr;

import :deleters;

namespace toy {

export {
    template <typename T, typename D = __detail::default_delete_verbose<T>>
    struct unique_ptr final {
    public:
        using element_type = T;
        using deleter_type = D;

        constexpr unique_ptr() noexcept
            : _ptr{ nullptr } {}

        unique_ptr( const unique_ptr & ) = delete;

        unique_ptr( nullptr_t ) noexcept
            : _ptr{ nullptr } {}
        unique_ptr( element_type *p ) noexcept
            : _ptr{ p } {};
        unique_ptr( unique_ptr<T, D> &&rhs ) noexcept
            : _ptr{ rhs.release() } {};

        ~unique_ptr() { std::invoke( deleter_type(), _ptr ); }

        unique_ptr &operator=( const unique_ptr & ) = delete;
        unique_ptr &operator=( unique_ptr &&rhs ) {
            if ( _ptr == rhs._ptr ) return *this;

            reset();
            std::swap( _ptr, rhs._ptr );
            return *this;
        }

        element_type &operator*() const { return *_ptr; }

        element_type *operator->() const noexcept { return _ptr; }

        explicit operator bool() const noexcept { return _ptr != nullptr; }

        element_type *get() const noexcept { return _ptr; }

        element_type *release() noexcept {
            const auto tmp = _ptr;
            _ptr = nullptr;
            return tmp;
            // possible:
            // return std::exchange(_ptr, nullptr);
        }

        void reset( element_type *other = nullptr ) {
            if ( _ptr == other ) return;

            element_type *tmp = std::exchange( _ptr, other );
            std::invoke( deleter_type(), tmp );
        }

    private:
        element_type *_ptr;
    };
}

}  // namespace toy
