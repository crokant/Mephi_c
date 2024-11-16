#pragma once

#include "ISorter.h"

template <class T>
class CountingSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        auto [minIt, maxIt] = std::minmax_element(begin, end, comp);
        int min = *minIt, max = *maxIt;
        int range = max - min + 1;

        int* count = new int[range]();
        for (auto i = begin; i != end; ++i) {
            count[*i - min]++;
        }

        auto out = begin;
        for (int i = 0; i < range; ++i) {
            while (count[i]-- > 0) {
                *out++ = i + min;
            }
        }
        delete[] count;
    }
};
