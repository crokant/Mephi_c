#pragma once

#include "ISorter.h"

template<class T>
class ShakerSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        bool swapped = true;
        auto left = begin;
        auto right = end - 1;

        while (swapped) {
            swapped = false;

            for (auto i = left; i < right; ++i) {
                if (comp(*(i + 1), *i)) {
                    std::swap(*i, *(i + 1));
                    swapped = true;
                }
            }
            if (!swapped) break;
            --right;
            swapped = false;
            for (auto i = right - 1; i >= left; --i) {
                if (comp(*(i + 1), *i)) {
                    std::swap(*i, *(i + 1));
                    swapped = true;
                }
            }
            ++left;
        }
    }
};
