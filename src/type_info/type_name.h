
#pragma once

#include <string>
#include <source_location>

namespace toy
{

namespace __detail
{

// NOTE: typename name ("T") necessary for proper output!!!
template <typename T> constexpr std::string_view wrapped_type_name() {
    return std::source_location::current().function_name();
}

constexpr std::size_t wrapper_type_name_prefix_len() {
    return wrapped_type_name<void>().find( "void" );
}

constexpr std::size_t wrapper_type_name_suffix_len() {
    return wrapped_type_name<void>().length() - wrapper_type_name_prefix_len() - std::string_view( "void" ).length();
}

} // namespace __detail

template <typename T> constexpr std::string_view type_name() {
    constexpr auto wrappedName = __detail::wrapped_type_name<T>();
    constexpr auto prefixLen = __detail::wrapper_type_name_prefix_len();
    constexpr auto suffixLen = __detail::wrapper_type_name_suffix_len();
    constexpr auto typeNameLen = wrappedName.length() - prefixLen - suffixLen;
    return wrappedName.substr( prefixLen, typeNameLen );
}

} // namespace toy