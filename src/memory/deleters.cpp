
module;

#include <print>

export module toy_std.memory:deleters;

namespace toy {

template <typename T>
struct default_delete {
    constexpr default_delete() noexcept = default;
    template <typename U>
    constexpr default_delete( const default_delete<U> & ) noexcept;
    constexpr void operator()( T *ptr ) const noexcept { delete ptr; };
};

template <typename T>
struct default_delete_verbose {
    constexpr default_delete_verbose() noexcept = default;
    template <typename U>
    constexpr default_delete_verbose(
        const default_delete_verbose<U> & ) noexcept;
    constexpr void operator()( T *ptr ) const noexcept {
        std::println( "default deleter called" );
        delete ptr;
    };
};

template <typename T>
struct default_delete<T[]> {
    constexpr default_delete() noexcept = default;
    template <typename U>
    constexpr default_delete( const default_delete<U> & ) noexcept;
    constexpr void operator()( T ptr[] ) const noexcept { delete[] ptr; };
};

template <typename T>
struct default_delete_verbose<T[]> {
    constexpr default_delete_verbose() noexcept = default;
    template <typename U>
    constexpr default_delete_verbose(
        const default_delete_verbose<U> & ) noexcept;
    constexpr void operator()( T ptr[] ) const noexcept {
        std::println( "default array deleter called" );
        delete[] ptr;
    };
};

export template <typename T>
struct deleter_pointer_wrapper {
    // NOTE: default constructor cause segfault in unique_ptr move cases
    // deleter_pointer_wrapper() = default;

    deleter_pointer_wrapper( void ( *pf )( T * ) )
        : pf_{ pf } {}

    void operator()( T *p ) { std::invoke( pf_, p ); }
    void ( *pf_ )( T * );
};

// =========================================================================
// =============== QT style deleters ========================================
// =========================================================================

template <typename T>
struct default_delete_qt {
    static inline void cleanup( T *pointer ) noexcept { delete pointer; }
    void operator()( T *pointer ) const noexcept { cleanup( pointer ); }
};

template <typename T>
struct default_delete_array_qt {
    static inline void cleanup( T *pointer ) noexcept { delete[] pointer; }
    void operator()( T *pointer ) const noexcept { cleanup( pointer ); }
};

}  // namespace toy
