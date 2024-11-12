#pragma once

#include "ISorter.h"

template<class T>
class BubbleSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        for (auto i = begin; i != end; ++i) {
            for (auto j = begin; j != end - 1; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::swap(*j, *(j + 1));
                }
            }
        }
    }
};