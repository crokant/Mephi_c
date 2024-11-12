#include <iostream>
#include "sorting/BubbleSorter.h"
#include "sorting/CountingSorter.h"


int main() {
    int arr[] = {4,2,1,5,10,7,8};
    DynamicArray<int> dynamic(arr, 7);

    int arr1[] = {4,2,1,5,10,7,8};
    DynamicArray<int> dynamic1(arr1, 7);

    BubbleSorter<int> sorter;
    CountingSorter<int> sorter1;
    sorter.sort(dynamic.begin(), dynamic.end());
    for(int i = 0; i < 7; i++) {
        std::cout << dynamic[i] << " ";
    }
    sorter1.sort(dynamic1.begin(), dynamic1.end());
    for(int i = 0; i < 7; i++) {
        std::cout << dynamic1[i] << " ";
    }
}