#include <iostream>
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "tests.h"

using namespace std;

int main() {
    test1();
    test2();
    test3();

    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    MutableArraySequence<int> mutableArraySeq(arr, arrSize);
    ImmutableArraySequence<int> immutableArraySeq(arr, arrSize);

    LinkedList<int> linkedList;
    linkedList.append(10);
    linkedList.append(20);
    linkedList.append(30);
    linkedList.append(40);
    MutableListSequence<int> listSeq1(linkedList);
    ImmutableListSequence<int> listSeq2(linkedList);
    return 0;
}
