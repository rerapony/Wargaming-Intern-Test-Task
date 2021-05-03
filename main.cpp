#include <iostream>
#include <cassert>

#include "even.hpp"
#include "fifo.hpp"
#include "sort.hpp"

void test_even() {
    assert(!task1::isEven(5));
    assert(task1::isEven(6));
    assert(task1::isEven(1378));
    assert(!task1::isEven(-111111));
    assert(task1::isEven(0));
}

void test_fifo() {
    size_t N = 5;
    int inputs[5] = {8, -1, 0, 999, 10};

    auto queue = task2::FIFOLinkedList<int>();
    for (size_t i = 0; i < N; ++i) {
        queue.append(inputs[i]);
    }

    for (size_t i = 0; i < N; ++i) {
        auto result = queue.pop();
        assert(result == inputs[i]);
    }

    auto queue2 = task2::FIFOArray<int>();
    for (size_t i = 0; i < N; ++i) {
        queue2.append(inputs[i]);
    }

    for (size_t i = 0; i < N; ++i) {
        auto result = queue2.pop();
        assert(result == inputs[i]);
    }
}

void test_sort() {
    const size_t length = 5;
    int arr[length] {8, 10, 2, 4, 0};

    task3::merge_sort(arr, 0, length-1);

    int sorted_array[length] {0, 2, 4, 8, 10};

    for (size_t i = 0; i<length; ++i) {
        assert(arr[i] == sorted_array[i]);
    }
}


int main() {
    test_even();
    test_fifo();
    test_sort();

    return 0;
}