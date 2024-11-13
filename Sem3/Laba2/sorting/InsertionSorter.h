#pragma once

#include "ISorter.h"

template<class T>
class InsertionSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        for (auto i = begin + 1; i != end; ++i) {
            T value = *i;
            auto j = i;
            while (j > begin && comp(value, *(j - 1))) {
                *j = *(j - 1);
                --j;
            }
            *j = value;
        }
    }
};