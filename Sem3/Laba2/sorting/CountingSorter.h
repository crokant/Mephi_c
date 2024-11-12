#pragma once

#include "ISorter.h"

template<class T>
class CountingSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        auto [minIt, maxIt] = std::minmax_element(begin, end, comp);
        int min = *minIt, max = *maxIt;

        std::vector<int> count(max - min + 1, 0);
        for (auto i = begin; i != end; ++i) count[*i - min]++;

        auto out = begin;
        for (int i = 0; i < count.size(); ++i) {
            while (count[i]-- > 0) {
                *out++ = i + min;
            }
        }
    }
};

