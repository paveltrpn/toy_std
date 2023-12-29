module;

export module toy_stl:list;

export {
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
}
