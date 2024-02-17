
module;

#include <type_traits>
#include <string>

export module toy_std.concepts;

export {
    namespace toy {

    template <typename T>
    concept Character
      = std::is_same_v<char, std::remove_cv_t<T>> || std::is_same_v<wchar_t, std::remove_cv_t<T>>;

    template <typename T>
    concept NumberOrString = std::is_integral_v<T> || std::is_floating_point_v<T>
                             || std::is_same_v<std::string, T> || std::is_same_v<std::wstring, T>;

    template <typename T>
    concept Arithmetical = std::is_signed_v<T> && requires(T value) {
        value + value;
        value - value;
        value *value;
        value / value;
    };

    template <typename T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    }  // namespace toy
}
