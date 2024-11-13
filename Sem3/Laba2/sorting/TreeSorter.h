#pragma once

#include "ISorter.h"
#include "../../../Sem2/Laba4/BinaryTree.h"


template<typename T>
class TreeSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        int mult = comp(0, 1) ? 1 : -1;

        BinaryTree<T> tree;
        for (auto i = begin; i != end; i++) {
            tree.add(*i * mult);
        }
        DynamicArray<T> sortedArray = tree.getInOrderTraversal();
        for (auto it = sortedArray.begin(); it != sortedArray.end(); ++it) {
            *it *= mult;
        }

        std::copy(sortedArray.begin(), sortedArray.end(), begin);

    }
};
