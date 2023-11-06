#ifndef __list_h_
#define __list_h_

namespace toy {

template <typename T>
struct list {
        struct Node {
            private:
                T data_;
                Node* prev_;
                Node* next_;
        };

    private:
        Node* front_;
        Node* back_;
};

}  // namespace toy

#endif
