
module;

#include <any>
#include <unordered_map>
#include <vector>

export module toy_std.type_info:registry;

import :type_index;

namespace toy {

export struct registry {
private:
    template <typename T>
    [[nodiscard]] auto &storage( std::size_t id = type_index<T>().value() ) {
        auto &st = pool_[id];

        if ( !st.has_value() ) {
            st.emplace<std::vector<T>>();
        }

        return std::any_cast<std::vector<T> &>( st );
    }

    template <typename T>
    [[nodiscard]] const auto *storage(
        std::size_t id = type_index<T>().value() ) const {
        if ( const auto it = pool_.find( id ); it != pool_.cend() ) {
            auto &store_ref =
                std::any_cast<const std::vector<T> &>( it->second );
            return &store_ref;
        }
        return static_cast<const std::vector<T> *>( nullptr );
    }

    /*
     * @brief
     * Поверяет, сохранялся ли когда‑нибудь тип T в registry.
     * Давайте попробуем получить указатель на вектор от этого типа T.
     * И у нас что‑то сохранялось, если это не пустой указатель на не пустой вектор.
     **/
    template <typename T>
    [[nodiscard]] bool has() const {
        auto *cpool = storage<std::decay_t<T>>();
        return cpool && !cpool->empty();
    }

public:
    template <typename T, typename... Args>
    auto &emplace( Args &&...args ) {
        return storage<T>().emplace_back( T{ std::forward<Args>( args )... } );
    }

    template <typename T>
    auto &emplace( T &&arg ) {
        return storage<T>().emplace_back( T{ std::forward<T>( arg ) } );
    }

    template <typename... T>
    [[nodiscard]] bool all_of() const {
        return ( has<T>() && ... );
    }

    template <typename... T>
    [[nodiscard]] bool any_of() const {
        return ( has<T>() || ... );
    }

    template <typename T>
    [[nodiscard]] const auto &all() const {
        return *storage<T>();
    }

    /* decltype(auto) чтобы вернуть по референсу в случае одного типа, и тупл ссылок
     * по значению в случае нескольких типов
     **/
    template <typename... T>
    [[nodiscard]] decltype( auto ) last() const {
        if constexpr ( sizeof...( T ) == 1u ) {
            return ( storage<T>()->back(), ... );
        } else {
            return std::forward_as_tuple( last<T>()... );
        }
    }

private:
    std::unordered_map<std::size_t, std::any> pool_;
};

}  // namespace toy
