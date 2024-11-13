#pragma once

#include "ISorter.h"

template<typename T>
class ShellSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        int n = end - begin;
        int gap = n / 2;

        while (gap > 0) {
            for (size_t i = gap; i < n; ++i) {
                auto temp = *(begin + i);
                size_t j = i;
                while (j >= gap && comp(temp, *(begin + j - gap))) {
                    *(begin + j) = *(begin + j - gap);
                    j -= gap;
                }
                *(begin + j) = temp;
            }
            gap /= 2;
        }
    }
};
