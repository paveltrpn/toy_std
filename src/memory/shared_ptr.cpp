
module;

#include <iostream>

export module toy_std.memory:shared_ptr;

import :deleters;

namespace toy {

template <typename T, typename D = default_delete_verbose<T>>
struct control_block {
public:
    using element_type = T;
    using deleter_type = D;

    ~control_block() { std::invoke( deleter_type(), _ptr ); }

    void ref() {
        _strongRefCount++;
        _weakRefCount++;
    };

    void unref() {
        _strongRefCount--;
        _weakRefCount--;
    };

    long long _strongRefCount{};
    long long _weakRefCount{};
    element_type *_ptr{};
};

export template <typename T>
struct shared_ptr;

export template <typename T>
struct weak_ptr {
public:
    using element_type = T;

    // constructors
    weak_ptr();
    template <typename Y>
    weak_ptr( shared_ptr<Y> const &r );
    weak_ptr( weak_ptr const &r );
    template <typename Y>
    weak_ptr( weak_ptr<Y> const &r );

    // destructor
    ~weak_ptr();

    // assignment
    weak_ptr &operator=( weak_ptr const &r );
    template <typename Y>
    weak_ptr &operator=( weak_ptr<Y> const &r );
    template <typename Y>
    weak_ptr &operator=( shared_ptr<Y> const &r );

    // modifiers
    void swap( weak_ptr &r ) noexcept;
    void reset();

    // observers
    [[nodiscard]]
    long use_count() const;

    [[nodiscard]]
    bool expired() const;

    shared_ptr<T> lock() const;

private:
    element_type *_ptr;
    element_type *_ctrlBlkPtr;
};

// comparison
template <typename T, typename U>
bool operator<( weak_ptr<T> const &a, weak_ptr<U> const &b );

// specialized algorithms
template <typename T>
void swap( weak_ptr<T> &a, weak_ptr<T> &b ) noexcept;

export template <typename T>
struct shared_ptr {
public:
    using element_type = T;

    // constructors
    shared_ptr()
        : _ptr{ nullptr }
        , _ctrlBlkPtr{ nullptr } {};
    template <typename Y>
    explicit shared_ptr( Y *p );
    template <typename Y, typename D>
    shared_ptr( Y *p, D d );
    shared_ptr( shared_ptr const &r );
    template <typename Y>
    shared_ptr( shared_ptr<Y> const &r );
    // template <typename Y> explicit shared_ptr( weak_ptr<Y> const &r );

    // destructor
    ~shared_ptr();

    // assignment
    shared_ptr &operator=( shared_ptr const &r );
    template <typename Y>
    shared_ptr &operator=( shared_ptr<Y> const &r );

    // modifiers
    void swap( shared_ptr &r ) noexcept;
    void reset();
    template <typename Y>
    void reset( Y *p );
    template <typename Y, typename D>
    void reset( Y *p, D d );

    // observers
    T *get() const { return _ptr; };
    T &operator*() const { return *_ptr; };
    T *operator->() const { return _ptr; };

    [[nodiscard]]
    long use_count() const {
        return _ctrlBlkPtr->_strongRefCount;
    };

    [[nodiscard]]
    bool unique() const;

    operator bool() const noexcept { return _ptr != nullptr; };

private:
    element_type *_ptr;
    control_block<T> *_ctrlBlkPtr;
};

// comparison
template <typename T, typename U>
bool operator==( shared_ptr<T> const &a, shared_ptr<U> const &b );

template <typename T, typename U>
bool operator!=( shared_ptr<T> const &a, shared_ptr<U> const &b );

template <typename T, typename U>
bool operator<( shared_ptr<T> const &a, shared_ptr<U> const &b );

// other operators
template <typename E, typename T, typename Y>
std::basic_ostream<E, T> &operator<<( std::basic_ostream<E, T> &os,
                                      shared_ptr<Y> const &p );

// specialized algorithms
template <typename T>
void swap( shared_ptr<T> &a, shared_ptr<T> &b );

// casts
template <typename T, typename U>
shared_ptr<T> static_pointer_cast( shared_ptr<U> const &r );

template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast( shared_ptr<U> const &r );

// get_deleter
template <typename D, typename T>
D *get_deleter( shared_ptr<T> const &p );

}  // namespace toy
