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


void print(DynamicArray<int> &dynamic, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << dynamic[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int arr[] = {4, 2, 1, 5, 10, 7, 8, 15, 3, 4, 0, 11, 20, 17, -2, -3, -15};
    int size = 17;
    DynamicArray<int> dynamic(arr, size);
    DynamicArray<int> dynamic1(arr, size);
    DynamicArray<int> dynamic2(arr, size);
    DynamicArray<int> dynamic3(arr, size);
    DynamicArray<int> dynamic4(arr, size);
    DynamicArray<int> dynamic5(arr, size);
    DynamicArray<int> dynamic6(arr, size);
    DynamicArray<int> dynamic7(arr, size);
    DynamicArray<int> dynamic8(arr, size);
    DynamicArray<int> dynamic9(arr, size);
    DynamicArray<int> dynamic10(arr, size);
    DynamicArray<int> dynamic11(arr, size);
    DynamicArray<int> dynamic12(arr, size);

    BubbleSorter<int> sorter;
    CountingSorter<int> sorter1;
    HeapSorter<int> sorter2;
    InsertionSorter<int> sorter3;
    MergeSorter<int> sorter4;
    QuickSorter<int> sorter5;
    SelectionSorter<int> sorter6;
    ShakerSorter<int> sorter7;
    BinaryInsertionSorter<int> sorter8;
    ImprovedSelectionSorter<int> sorter9;
    TreeSorter<int> sorter10;
    ShellSorter<int> sorter11;


    sorter.sort(dynamic.begin(), dynamic.end());
    sorter1.sort(dynamic1.begin(), dynamic1.end());
    sorter2.sort(dynamic2.begin(), dynamic2.end());
    sorter3.sort(dynamic3.begin(), dynamic3.end());
    sorter4.sort(dynamic4.begin(), dynamic4.end());
    sorter5.sort(dynamic5.begin(), dynamic5.end());
    sorter6.sort(dynamic6.begin(), dynamic6.end());
    sorter7.sort(dynamic7.begin(), dynamic7.end());
    sorter8.sort(dynamic8.begin(), dynamic8.end());
    sorter9.sort(dynamic9.begin(), dynamic9.end());
    sorter10.sort(dynamic10.begin(), dynamic10.end());
    sorter11.sort(dynamic11.begin(), dynamic11.end());

    print(dynamic, size);
    print(dynamic1, size);
    print(dynamic2, size);
    print(dynamic3, size);
    print(dynamic4, size);
    print(dynamic5, size);
    print(dynamic6, size);
    print(dynamic7, size);
    print(dynamic8, size);
    print(dynamic9, size);
    print(dynamic10, size);
    print(dynamic11, size);
}