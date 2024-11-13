#pragma once

#include "ISorter.h"

template<class T>
class ImprovedSelectionSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        for (auto i = begin; i < end - 1; ++i) {
            auto minIndex = i;
            for (auto j = i + 1; j < end; ++j) {
                if (comp(*(j), *(minIndex))) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap(*i, *minIndex);
            }
        }
    }
};
