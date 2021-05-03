#pragma once

/* QuickSort дает O(N^2) в худшем случае, может плохо себя вести в случае отсортированного массива
 * MergeSort дает O(logN) во всех, но занимает много места в памяти
 * HeapSort дает O(logN), но не стабилен
 * Insertion Sort дает O(n) для отсортированного массива, но O(n^2) для отсортированного в обратном порядке
 * Реализуем MergeSort - мы не знаем какой будет вход и хотим хорошую сортировку на всех входах,
 * про память в задаче ничего не сказано, у MergeSort меньшая константа, можно распаралеллить, стабильная */

template <typename T>
void merge(T arr[], size_t l, size_t m, size_t r)
{
    size_t i, j, k;
    size_t size_left = m - l + 1;
    size_t size_right =  r - m;

    T L[size_left], R[size_right];

    for (i = 0; i < size_left; ++i)
        L[i] = std::move(arr[l + i]);
    for (j = 0; j < size_right; ++j)
        R[j] = std::move(arr[m + 1 + j]);

    i = j = 0;
    k = l;

    while (i < size_left && j < size_right)
    {
        if (L[i] <= R[j])
        {
            arr[k] = std::move(L[i]);
            i++;
        }
        else
        {
            arr[k] = std::move(R[j]);
            j++;
        }
        k++;
    }

    while (i < size_left)
    {
        arr[k] = std::move(L[i]);
        i++;
        k++;
    }

    while (j < size_right)
    {
        arr[k] = std::move(R[j]);
        j++;
        k++;
    }
}

template <typename T>
void merge_sort(T arr[], size_t l, size_t r) {
    if (l < r) {
        size_t m = (l + r) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge<T>(arr, l, m, r);
    }
}
