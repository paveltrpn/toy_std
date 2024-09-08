
module;

#include <cassert>
#include <cstring>

export module toy_std.string;

namespace toy {

// int ft_memcmp(void const *s1, void const *s2, size_t n)
// {
// 	int		res;
// 	t_byte	*ps1;
// 	t_byte	*ps2;
// 	res = 0;
// 	if (s1 == s2)
// 		return (res);
// 	ps1 = (t_byte*)s1;
// 	ps2 = (t_byte*)s2;
// 	while (n-- && !res)
// 		res = *ps1++ - *ps2++;
// 	return (res);
// }
// 
// int ft_strcmp(char const *s1, char const *s2)
// {
// 	size_t len;
// 	len = ft_min(ft_strlen(s1) + 1, ft_strlen(s2) + 1);
// 	return (ft_memcmp(s1, s2, len));
// }

struct basic_string final {
    public:
        using value_type = char;

        basic_string() : data_{ empty_ } {};

        // string literal (const char*) constructor
        basic_string(const char *value) {
            if (!value || !*value) {
                data_ = empty_;
            } else {
                data_ = populate(value);
            }
        };

        basic_string(const basic_string &value) {
            if (value.data_ == empty_) {
                data_ = empty_;
            } else {
                data_ = populate(value.data_);
            }
        };

        basic_string(basic_string &&rhs) noexcept {};

        basic_string &operator=(const basic_string &rhs) {
        }

        basic_string &operator=(basic_string &&rhs) noexcept {
        }

        ~basic_string() {
            delete[] data_;
        }

        [[nodiscard]]
        size_t length() const {
            return strlen(data_);
        }

        bool operator==(const basic_string &rhs) const {
            if (length() != rhs.length()) {
                return false;
            } else {
                return strcmp(data_, rhs.data_);
            }
        }

    private:
        static constexpr value_type empty_[1] = { '\0' };
        static const value_type *populate(const value_type *str) {
            assert(str && *str);
            size_t capacity = strlen(str) + 1;
            auto *tmp = new value_type[capacity];
            memcpy(tmp, str, capacity);
            return tmp;
        };

    private:
        const value_type *data_;
};

export {
    using string = basic_string;
}

}  // namespace toy
