#pragma once

namespace task2 {
    template<typename T>
    struct FIFOLinkedList {
    public:
        struct Node {
            explicit Node(const T &data) : data(data), next(nullptr) {}

            explicit Node(T &&data) : data(std::move(data)), next(nullptr) {}

            T data;
            Node *next;
        };

        FIFOLinkedList() : first(nullptr), last(nullptr) {}

        void append(T &&data) {
            Node *node = new Node(std::forward<T>(data));

            if (first == nullptr) {
                first = node;
            } else {
                last->next = node;
            }
            last = node;
        }

        void append(T &data) {
            append(std::move(data));
        }

        T pop() {
            if (first != nullptr) {
                if (first->next != nullptr) {
                    Node *node = first;
                    first = node->next;
                    T data = std::move(node->data);
                    delete node;
                    return data;
                } else {
                    Node *node = first;
                    T data = std::move(node->data);
                    delete node;
                    first = last = nullptr;
                    return data;
                }
            }

            throw std::out_of_range("FIFO is empty\n");
        }

        ~FIFOLinkedList() {
            while (first != nullptr)
                pop();
        }

    private:
        Node *first;
        Node *last;
    };


    template<typename T>
    class FIFOArray {
    public:
        explicit FIFOArray(size_t new_capacity) : first(0), last(0), capacity(new_capacity), arr(new T[new_capacity]) {}

        FIFOArray() : first(0), last(0), arr(new T[capacity]) {}

        void append(T &&data) {
            if (last == capacity)
                throw std::out_of_range("FIFO is full\n");
            arr[last] = data;
            last++;

        }

        void append(T &data) {
            append(std::move(data));
        }

        T pop() {
            if (last == first)
                throw std::out_of_range("FIFO is empty\n");

            T data = std::move(arr[0]);
            for (size_t i = 0; i < last - 1; ++i) {
                arr[i] = std::move(arr[i + 1]);
            }
            last--;
            return data;
        }

        ~FIFOArray() {
            delete[] arr;
        }

    private:
        size_t first, last;
        size_t capacity = 20;
        T *arr;
    };
}