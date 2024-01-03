
module;

#include <memory>

export module toy_stl.list;

namespace toy {

struct node_base {
        std::shared_ptr<node_base> next_;
        std::shared_ptr<node_base> prev_;
};

template <typename T>
struct node : public node_base {
        node(const T& data) : data_{ data } {
        }

        T* valptr() {
            return std::addressof(data_);
        }

        const T* valptr() const {
            return std::addressof(data_);
        }

        T operator()() {
            return data_;
        }

    private:
        T data_{};
};

template <typename T>
struct list_iterator {
        using self_ = list_iterator<T>;
        using node_ = node<T>;

        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = node_&;
        using pointer = node_*;
        using iterator_category = std::bidirectional_iterator_tag;
    
        list_iterator(): valuePtr_{} {};
        explicit list_iterator(node_base* ptr) : valuePtr_{ ptr } {};

        reference operator*() {
            return *static_cast<node_*>(valuePtr_)->valptr();
        };

        pointer operator->() {
            return std::addressof(static_cast<node_*>(valuePtr_)->valptr());
        }

        // pre-increment
        self_& operator++() {
            valuePtr_ = valuePtr_->next_;
            return *this;
        }

        // post-increment
        self_ operator++(int) {
            auto tmp{ *this };
            ++(*this);
            return tmp;
        }

        // pre-decrement
        self_& operator--() {
            valuePtr_ = valuePtr_->prev_;
            return *this;
        }

        // post-decrement
        self_ operator--(int) {
            auto tmp{ *this };
            --(*this);
            return tmp;
        }

        friend bool operator==(const self_& a, const self_& b) {
            return a.valuePtr_ == b.valuePtr_;
        };

        friend bool operator!=(const self_& a, const self_& b) {
            return !(a == b);
        };

    private:
        std::shared_ptr<node_base> valuePtr_;
};

export template <typename T>
struct list {
        using iterator = list_iterator<T>;
        using value_type = T;

        explicit list() = default;

        list(const list& rhs) = delete;
        list(list&& rhs) = delete;

        list& operator=(const list& rhs) = delete;
        list& operator=(list&& rhs) = delete;

        iterator begin() {
            return iterator{ front_ };
        }

        iterator end() {
            return iterator{};
        }

        void push(const T& rhs) {
            ++size_;
        }

        T& pop() {
        }

    private:
        std::shared_ptr<node<T>> front_{};
        std::shared_ptr<node<T>> back_{};

        size_t size_{};
};

}  // namespace toy
