#pragma once

#include "ISorter.h"

template<class T>
class SelectionSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        for (auto i = begin; i < end - 1; ++i) {
            auto minElement = i;
            for (auto j = i + 1; j < end; ++j) {
                if (comp(*j, *minElement)) {
                    minElement = j;
                }
            }
            if (minElement != i) {
                std::swap(*i, *minElement);
            }
        }
    }
};
