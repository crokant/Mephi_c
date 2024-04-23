#pragma once

#include <iostream>
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include <cassert>

//test dynamic array
void test1() {
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;

    DynamicArray<int> dynamicArr(arr, arrSize);
    assert(dynamicArr.getSize() == arrSize);
    for (int i = 0; i < arrSize; i++) {
        assert(dynamicArr.get(i) == arr[i]);
    }

    int newSize = 10;
    int newValue = 100;

    dynamicArr.setSize(newSize);
    assert(dynamicArr.getSize() == newSize);

    dynamicArr.set(7, newValue);
    assert(dynamicArr.get(7) == newValue);
    std::cout << "TEST 1 PASSED!" << std::endl;

}

//test linked list
void test2() {
    LinkedList<int> linkedList1;
    assert(linkedList1.getLength() == 0);

    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    LinkedList<int> linkedList2(arr, arrSize);
    assert(linkedList2.getLength() == arrSize);
    assert(linkedList2.getFirst() == 1);
    assert(linkedList2.getLast() == 5);
    assert(linkedList2.get(2) == 3);

    linkedList1.append(10);
    linkedList1.prepend(20);
    linkedList1.append(30);
    assert(linkedList1.getLength() == 3);
    assert(linkedList1.getFirst() == 20);
    assert(linkedList1.getLast() == 30);
    assert(linkedList1.get(1) == 10);

    linkedList1.prepend(5);
    assert(linkedList1.getLength() == 4);
    assert(linkedList1.getFirst() == 5);

    linkedList1.insert(2, 15);
    assert(linkedList1.getLength() == 5);
    assert(linkedList1.get(2) == 15);
    assert(linkedList1.getLast() == 30);

    auto sublist = linkedList1.getSubList(1, 3);
    assert(sublist->getLength() == 3);
    assert(sublist->getFirst() == 20);
    delete sublist;

    assert(linkedList1.getLength() == 5);
    std::cout << "TEST 2 PASSED!" << std::endl;

}

//test immutable array sequence
void test3() {
// Test default constructor
    ImmutableArraySequence<int> immutableArraySeq1;
    assert(immutableArraySeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    ImmutableArraySequence<int> immutableArraySeq2(arr, arrSize);
    assert(immutableArraySeq2.getLength() == arrSize);
    assert(immutableArraySeq2.getFirst() == 1);
    assert(immutableArraySeq2.getLast() == 5);
    assert(immutableArraySeq2.get(2) == 3);

    // Test getSubSequence
    auto subSeq = immutableArraySeq2.getSubSequence(1, 3);
    assert(subSeq->getLength() == 3);
    assert(subSeq->getFirst() == 2);
    assert(subSeq->getLast() == 4);
    // Test append
    auto appendedSeq = immutableArraySeq2.append(6);
    assert(appendedSeq->getLength() == arrSize + 1);
    assert(appendedSeq->getLast() == 6);

    // Test prepend
    auto prependedSeq = immutableArraySeq2.prepend(0);
    /*
    assert(prependedSeq->getLength() == arrSize + 1);
    assert(prependedSeq->getFirst() == 0);

    // Test insertAt
    auto insertedSeq = immutableArraySeq2.insertAt(2, 10);
    assert(insertedSeq->getLength() == arrSize + 1);
    assert(insertedSeq->get(2) == 10);

    // Test concat
    ImmutableArraySequence<int> otherArrSeq(arr, arrSize);
    auto concatenatedSeq = immutableArraySeq2.concat(&otherArrSeq);
    assert(concatenatedSeq->getLength() == arrSize * 2);
    assert(concatenatedSeq->getLast() == 5); // last element of original array
    */
    std::cout << "TEST 3 PASSED!" << std::endl;
}