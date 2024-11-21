#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>
#include "tests.h"
#include "sorting/ISorter.h"
#include "sorting/ShellSorter.h"
#include "sorting/HeapSorter.h"
#include "sorting/QuickSorter.h"
#include "sorting/BubbleSorter.h"
#include "sorting/CountingSorter.h"
#include "sorting/ImprovedSelectionSorter.h"
#include "sorting/InsertionSorter.h"
#include "sorting/MergeSorter.h"
#include "sorting/SelectionSorter.h"
#include "sorting/ShakerSorter.h"
#include "sorting/TreeSorter.h"
#include "sorting/BinaryInsertionSorter.h"
#include "DataGenerator.h"

void sortersFunctionalityTest(ISorter<Student> &sorter, const std::string &sorterName, int dataSize);

void sortersFunctionalityTest(ISorter<int> &sorter, const std::string &sorterName, int dataSize);

void sortersPerformanceTest(ISorter<int> &sorter, const std::string &sorterName);

void sortersPerformanceTest(ISorter<Student> &sorter, const std::string &sorterName);

template<typename T>
void runTests(bool load = false) {

    std::unordered_map<std::string, ISorter<T> *> sorters = {
            {"ShellSorter",             new ShellSorter<T>()},
            {"HeapSorter",              new HeapSorter<T>()},
            {"QuickSorter",             new QuickSorter<T>()},
            {"BubbleSorter",            new BubbleSorter<T>()},
            {"CountingSorter",          new CountingSorter<T>()},
            {"ImprovedSelectionSorter", new ImprovedSelectionSorter<T>()},
            {"InsertionSorter",         new InsertionSorter<T>()},
            {"MergeSorter",             new MergeSorter<T>()},
            {"SelectionSorter",         new SelectionSorter<T>()},
            {"ShakerSorter",            new ShakerSorter<T>()},
            {"TreeSorter",              new TreeSorter<T>()},
            {"BinaryInsertionSorter",   new BinaryInsertionSorter<T>()}
    };

    if (!load) {
        for (auto &entry: sorters) {
            sortersFunctionalityTest(*entry.second, entry.first, 100);
        }
    } else {
        std::cout << std::setw(25) << std::left << "Sorter"
                  << std::setw(10) << std::right << "Data Size"
                  << std::setw(25) << std::right << "Time (microseconds)" << std::endl;
        for (auto &entry: sorters) {
            sortersPerformanceTest(*entry.second, entry.first);
        }
    }
    for (auto &entry: sorters) {
        delete entry.second;
    }
}
