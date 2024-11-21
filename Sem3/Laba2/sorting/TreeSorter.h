#pragma once

#include "ISorter.h"
#include "../../../Sem2/Laba4/BinaryTree.h"


template<typename T>
class TreeSorter : public ISorter<T> {
public:
    void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        BinaryTree<T> tree;

        for (auto i = begin; i != end; i++) {
            tree.addWithComp(*i, comp);
        }

        DynamicArray<T> sortedArray = tree.getInOrderTraversal();
        std::copy(sortedArray.begin(), sortedArray.end(), begin);
    }
};
