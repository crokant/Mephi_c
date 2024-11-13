#pragma once

#include "ISorter.h"

template<class T>
class QuickSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        quickSort(begin, end, comp);
    }

private:
    void quickSort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
                   std::function<bool(const T &, const T &)> &comp) {
        if (begin + 1 >= end) {
            return;
        }
        auto pivot = *(begin + (end - begin) / 2);
        auto left = begin;
        auto right = end - 1;
        while (left <= right) {
            while (comp(*left, pivot)) {
                ++left;
            }
            while (comp(pivot, *right)) {
                --right;
            }
            if (left <= right) {
                std::swap(*left, *right);
                ++left;
                --right;
            }
        }
        if (begin < right) {
            quickSort(begin, right + 1, comp);
        }
        if (left < end) {
            quickSort(left, end, comp);
        }
    }
};