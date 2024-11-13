#pragma once

#include "ISorter.h"

template<class T>
class BinaryInsertionSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        for (auto i = begin + 1; i != end; ++i) {
            T value = *i;
            auto low = begin;
            auto high = i;

            while (low < high) {
                auto mid = low + (high - low) / 2;
                if (comp(value, *mid)) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }

            auto pos = high;
            for (auto j = i; j > pos; --j) {
                *j = *(j - 1);
            }
            *pos = value;
        }
    }
};
