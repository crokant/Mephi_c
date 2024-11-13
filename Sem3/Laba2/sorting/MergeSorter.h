#pragma once

#include "ISorter.h"

template<class T>
class MergeSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        if (end - begin <= 1) return;
        auto mid = begin + (end - begin) / 2;

        sort(begin, mid, comp);
        sort(mid, end, comp);

        merge(begin, mid, end, comp);
    }

private:
    void merge(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator mid,
               typename DynamicArray<T>::Iterator end,
               std::function<bool(const T &, const T &)> comp) {
        int n1 = mid - begin;
        int n2 = end - mid;

        DynamicArray<T> left(n1), right(n2);
        for (int i = 0; i < n1; ++i) {
            left[i] = *(begin + i);
        }
        for (int i = 0; i < n2; ++i) {
            right[i] = *(mid + i);
        }

        int leftIndex = 0, rightIndex = 0, mergedIndex = 0;

        while (leftIndex < n1 && rightIndex < n2) {
            if (comp(left[leftIndex], right[rightIndex])) {
                *(begin + mergedIndex) = left[leftIndex];
                ++leftIndex;
            } else {
                *(begin + mergedIndex) = right[rightIndex];
                ++rightIndex;
            }
            ++mergedIndex;
        }

        while (leftIndex < n1) {
            *(begin + mergedIndex) = left[leftIndex];
            ++leftIndex;
            ++mergedIndex;
        }

        while (rightIndex < n2) {
            *(begin + mergedIndex) = right[rightIndex];
            ++rightIndex;
            ++mergedIndex;
        }
    }
};
