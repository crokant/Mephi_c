#include <cassert>
#include <iostream>
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

bool isSorted(const DynamicArray<int> &dynamic) {
    for (int i = 1; i < dynamic.getSize() - 1; ++i) {
        if (dynamic[i] < dynamic[i - 1]) {
            return false;
        }
    }
    return true;
}

void sortersTest(ISorter<int> &sorter) {
    int arr[100];
    generateRandomArray(arr, 100, INT_MIN / 100, INT_MAX / 100);
    DynamicArray<int> dynamic(arr, 100);
    sorter.sort(dynamic.begin(), dynamic.end(), [](const int &a, const int &b) { return a < b; });
    if (!isSorted(dynamic)) {
        std::cout << "fail" << std::endl;
    }
}

void test() {
    ShellSorter<int> shellSorter;
    HeapSorter<int> heapSorter;
    QuickSorter<int> quickSorter;
    BubbleSorter<int> bubbleSorter;
    CountingSorter<int> countingSorter;
    ImprovedSelectionSorter<int> improvedSelectionSorter;
    InsertionSorter<int> insertionSorter;
    MergeSorter<int> mergeSorter;
    SelectionSorter<int> selectionSorter;
    ShakerSorter<int> shakerSorter;
    TreeSorter<int> treeSorter;
    BinaryInsertionSorter<int> binaryInsertionSorter;

    sortersTest(shellSorter);
    sortersTest(heapSorter);
    sortersTest(quickSorter);
    sortersTest(bubbleSorter);
    sortersTest(countingSorter);
    sortersTest(improvedSelectionSorter);
    sortersTest(insertionSorter);
    sortersTest(mergeSorter);
    sortersTest(selectionSorter);
    sortersTest(shakerSorter);
    sortersTest(treeSorter);
    sortersTest(binaryInsertionSorter);

    std::cout << "Sorting tests passed!" << std::endl;
}
