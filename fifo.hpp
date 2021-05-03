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

        FIFOLinkedList() : first(nullptr), last(nullptr), size(0) {}

        FIFOLinkedList(const FIFOLinkedList& fifo): first(nullptr), last(nullptr), size(0) {
            Node *tmp = fifo.first;

            while (tmp != nullptr) {
                append(tmp->data);
                tmp = tmp->next;
            }
        }

        FIFOLinkedList& operator=(const FIFOLinkedList& fifo) {
            if (this == &fifo) {
                return *this;
            }

            while (first != nullptr) {
                pop();
            }

            Node *tmp = fifo.first;

            while (tmp != nullptr) {
                append(tmp->data);
                tmp = tmp->next;
            }
        }

        void append(T &&data) {
            Node *node = new Node(std::forward<T>(data));

            if (first == nullptr) {
                first = node;
            } else {
                last->next = node;
            }
            size++;
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
                    size--;
                    return data;
                } else {
                    Node *node = first;
                    T data = std::move(node->data);
                    delete node;
                    first = last = nullptr;
                    size--;
                    return data;
                }
            }

            throw std::out_of_range("FIFO is empty\n");
        }

        const T& operator[](size_t i) const {
            return get(i);
        }

        T& operator[](size_t i) {
            return get(i);
        }

        ~FIFOLinkedList() {
            while (first != nullptr)
                pop();
        }

    private:
        T& get(size_t i) {
            if (i < size) {
                Node *elem = first;
                for (size_t j = 0; j < i; ++j) {
                    elem = elem->next;
                }

                return elem->data;
            }

            throw std::out_of_range("Index out of range\n");
        }

        Node *first;
        Node *last;
        size_t size;
    };


    template<typename T>
    class FIFOStaticArray {
    public:
        explicit FIFOStaticArray(size_t new_capacity) : first(0), last(0), capacity(new_capacity), arr(new T[new_capacity]) {}

        FIFOStaticArray() : first(0), last(0), capacity(20), arr(new T[capacity]) {}

        FIFOStaticArray(const FIFOStaticArray& fifo) : first(fifo.first), last(fifo.last), capacity(fifo.capacity), arr(new T[capacity]) {
            std::copy(fifo.arr, fifo.arr + fifo.last, arr);
        }

        FIFOStaticArray& operator=(const FIFOStaticArray& fifo) {
            if (this == &fifo) {
                return *this;
            }

            first = fifo.first;
            last = fifo.last;
            capacity = fifo.capacity;
            delete[] arr;
            arr = new T[capacity];

            std::copy(fifo.arr, fifo.arr + fifo.last, arr);
        }

        void append(T &&data) {
            if (last == capacity) {
                throw std::out_of_range("FIFO is full\n");
            }
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

        const T& operator[](size_t i) const {
            return get(i);
        }

        T& operator[](size_t i) {
            return get(i);
        }

        ~FIFOStaticArray() {
            delete[] arr;
        }

    private:
        T& get(size_t i) {
            if (i < last) {
                return arr[i];
            }

            throw std::out_of_range("Index out of range");
        }

        size_t first, last;
        size_t capacity;
        T *arr;
    };
}