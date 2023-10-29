
#ifndef __concepts_h__
#define __concepts_h__

#include <type_traits>
#include <string>

namespace toy {

template <typename T>
concept Character
  = std::is_same_v<char, std::remove_cv_t<T>> || std::is_same_v<wchar_t, std::remove_cv_t<T>>;

template <typename T>
concept NumberOrString = std::is_integral_v<T> || std::is_floating_point_v<T>
                         || std::is_same_v<std::string, T> || std::is_same_v<std::wstring, T>;

template <typename T>
concept Arithmetical = requires(T value) {
    value + value;
    value - value;
    value *value;
    value / value;
};

}  // namespace toy
#endif
