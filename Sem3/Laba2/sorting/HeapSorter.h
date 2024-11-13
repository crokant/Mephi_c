#pragma once

#include "ISorter.h"

template<class T>
class HeapSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        int n = end - begin;

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(begin, n, i, comp);
        }

        for (int i = n - 1; i > 0; i--) {
            std::swap(begin[0], begin[i]);
            heapify(begin, i, 0, comp);
        }
    }

private:
    void heapify(typename DynamicArray<T>::Iterator begin, int heapSize, int rootIndex,
                 std::function<bool(const T &, const T &)> comp) {
        int largest = rootIndex;
        int left = 2 * rootIndex + 1;
        int right = 2 * rootIndex + 2;


        if (left < heapSize && comp(begin[largest], begin[left])) {
            largest = left;
        }

        if (right < heapSize && comp(begin[largest], begin[right])) {
            largest = right;
        }

        if (largest != rootIndex) {
            std::swap(begin[rootIndex], begin[largest]);
            heapify(begin, heapSize, largest, comp);
        }
    }
};