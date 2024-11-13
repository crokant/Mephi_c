#pragma once

#include <iostream>
#include "sorting/BubbleSorter.h"
#include "sorting/CountingSorter.h"
#include "sorting/HeapSorter.h"
#include "sorting/InsertionSorter.h"
#include "sorting/MergeSorter.h"
#include "sorting/QuickSorter.h"
#include "sorting/SelectionSorter.h"
#include "sorting/ShakerSorter.h"
#include "sorting/BinaryInsertionSorter.h"
#include "sorting/ImprovedSelectionSorter.h"
#include "sorting/TreeSorter.h"
#include "sorting/ShellSorter.h"


#include "../Laba1/UniquePtr.h"
template<typename T>
class SortAdapter {
private:
    UniquePtr<DynamicArray<T>> data;
    UniquePtr<ISorter<T>> sorter;

public:
    explicit SortAdapter() : data(nullptr), sorter(nullptr) {}

    void setData(UniquePtr<DynamicArray<T>> inputData) {
        data = std::move(inputData);
    }

    void setSorter(UniquePtr<ISorter<T>> inputSorter) {
        sorter = std::move(inputSorter);
    }

    void sort(std::function<bool(const T &, const T &)> comp = std::less<T>()) {
        if (data && sorter) {
            sorter->sort(data->begin(), data->end(), comp);
        } else {
            throw std::runtime_error("Data or sorter not set");
        }
    }

    void printData() const {
        if (data) {
            for (const auto &item: *data) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        } else {
            throw std::runtime_error("Data not set");
        }
    }

    UniquePtr<DynamicArray<T>> &getData() {
        return data;
    }
};