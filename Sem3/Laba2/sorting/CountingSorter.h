#pragma once

#include "ISorter.h"
#include <map>

template<class T>
class CountingSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        std::map<T, int, decltype(comp)> count(comp);

        for (auto i = begin; i != end; ++i) {
            count[*i]++;
        }
        auto out = begin;
        for (const auto &pair: count) {
            for (int i = 0; i < pair.second; ++i) {
                *out++ = pair.first;
            }
        }
    }
};
