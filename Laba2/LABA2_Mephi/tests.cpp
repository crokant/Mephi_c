#include <iostream>
#include "tests.h"
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
    int arrSize = 5;
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
    assert(concatenatedSeq->getLast() == 5);

    std::cout << "TEST 3 PASSED!" << std::endl;
}

//test mutable array sequence
void test4() {
    // Test default constructor
    MutableArraySequence<int> mutableArraySeq1;
    assert(mutableArraySeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
    MutableArraySequence<int> mutableArraySeq2(arr, arrSize);
    assert(mutableArraySeq2.getLength() == arrSize);
    assert(mutableArraySeq2.getFirst() == 1);
    assert(mutableArraySeq2.getLast() == 5);
    assert(mutableArraySeq2.get(2) == 3);

    // Test getSubSequence
    auto subSeq = mutableArraySeq2.getSubSequence(1, 3);
    assert(subSeq->getLength() == 3);
    assert(subSeq->getFirst() == 2);
    assert(subSeq->getLast() == 4);

    // Test append
    mutableArraySeq2.append(6);
    assert(mutableArraySeq2.getLength() == arrSize + 1);
    assert(mutableArraySeq2.getLast() == 6);

    // Test prepend
    mutableArraySeq2.prepend(0);
    assert(mutableArraySeq2.getLength() == arrSize + 2);
    assert(mutableArraySeq2.getFirst() == 0);

    // Test insertAt
    mutableArraySeq2.insertAt(2, 10);
    assert(mutableArraySeq2.getLength() == arrSize + 3);
    assert(mutableArraySeq2.get(2) == 10);

    // Test concat
    int arr2[] = {7, 8, 9};
    int arr2Size = 3;
    MutableArraySequence<int> otherArraySeq(arr2, arr2Size);
    assert((mutableArraySeq2.concat(&otherArraySeq))->getLast() == 9);
    assert(mutableArraySeq2.getLength() == arrSize + arr2Size);

    std::cout << "TEST 4 PASSED!" << std::endl;
}

//test immutable array sequence
void test5() {
    // Test default constructor
    ImmutableArraySequence<int> immutableArraySeq1;
    assert(immutableArraySeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
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
    assert(concatenatedSeq->getLast() == 5);

    std::cout << "TEST 5 PASSED!" << std::endl;
}

//test mutable array sequence
void test6() {
    // Test default constructor
    MutableArraySequence<int> mutableArraySeq1;
    assert(mutableArraySeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
    MutableArraySequence<int> mutableArraySeq2(arr, arrSize);
    assert(mutableArraySeq2.getLength() == arrSize);
    assert(mutableArraySeq2.getFirst() == 1);
    assert(mutableArraySeq2.getLast() == 5);
    assert(mutableArraySeq2.get(2) == 3);

    // Test getSubSequence
    auto subSeq = mutableArraySeq2.getSubSequence(1, 3);
    assert(subSeq->getLength() == 3);
    assert(subSeq->getFirst() == 2);
    assert(subSeq->getLast() == 4);

    // Test append
    mutableArraySeq2.append(6);
    assert(mutableArraySeq2.getLength() == arrSize + 1);
    assert(mutableArraySeq2.getLast() == 6);

    // Test prepend
    mutableArraySeq2.prepend(0);
    assert(mutableArraySeq2.getLength() == arrSize + 2);
    assert(mutableArraySeq2.getFirst() == 0);

    // Test insertAt
    mutableArraySeq2.insertAt(2, 10);
    assert(mutableArraySeq2.getLength() == arrSize + 3);
    assert(mutableArraySeq2.get(2) == 10);

    // Test concat
    MutableArraySequence<int> otherArrSeq(arr, arrSize);
    auto concatSeq = mutableArraySeq2.concat(&otherArrSeq);
    assert(concatSeq->getLength() == arrSize * 2 + 3);
    assert(concatSeq->getLast() == 5);
    std::cout << "TEST 6 PASSED!" << std::endl;
}

void test7() {
    // Test default constructor
    ImmutableListSequence<int> immutableListSeq1;
    assert(immutableListSeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
    ImmutableListSequence<int> immutableListSeq2(arr, arrSize);
    assert(immutableListSeq2.getLength() == arrSize);
    assert(immutableListSeq2.getFirst() == 1);
    assert(immutableListSeq2.getLast() == 5);
    assert(immutableListSeq2.get(2) == 3);

    // Test getSubSequence
    auto subSeq = immutableListSeq2.getSubSequence(1, 3);
    assert(subSeq->getLength() == 3);
    assert(subSeq->getFirst() == 2);
    assert(subSeq->getLast() == 4);

    // Test append
    auto appendedSeq = immutableListSeq2.append(6);
    assert(appendedSeq->getLength() == arrSize + 1);
    assert(appendedSeq->getLast() == 6);

    // Test prepend
    auto prependedSeq = immutableListSeq2.prepend(0);
    assert(prependedSeq->getLength() == arrSize + 1);
    assert(prependedSeq->getFirst() == 0);

    // Test insertAt
    auto insertedSeq = immutableListSeq2.insertAt(2, 10);
    assert(insertedSeq->getLength() == arrSize + 1);
    assert(insertedSeq->get(2) == 10);

    // Test concat
    ImmutableListSequence<int> otherListSeq(arr, arrSize);
    auto concatenatedSeq = immutableListSeq2.concat(&otherListSeq);
    assert(concatenatedSeq->getLength() == arrSize * 2);
    assert(concatenatedSeq->getLast() == 5);

    std::cout << "TEST 7 PASSED!" << std::endl;
}

void test8() {
    // Test default constructor
    MutableListSequence<int> mutableListSeq1;
    assert(mutableListSeq1.getLength() == 0);

    // Test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;
    MutableListSequence<int> mutableListSeq2(arr, arrSize);
    assert(mutableListSeq2.getLength() == arrSize);
    assert(mutableListSeq2.getFirst() == 1);
    assert(mutableListSeq2.getLast() == 5);
    assert(mutableListSeq2.get(2) == 3);

    // Test getSubSequence
    auto subSeq = mutableListSeq2.getSubSequence(1, 3);
    assert(subSeq->getLength() == 3);
    assert(subSeq->getFirst() == 2);
    assert(subSeq->getLast() == 4);

    // Test append
    mutableListSeq2.append(6);
    assert(mutableListSeq2.getLength() == arrSize + 1);
    assert(mutableListSeq2.getLast() == 6);

    // Test prepend
    mutableListSeq2.prepend(0);
    assert(mutableListSeq2.getLength() == arrSize + 2);
    assert(mutableListSeq2.getFirst() == 0);

    // Test insertAt
    mutableListSeq2.insertAt(2, 10);
    assert(mutableListSeq2.getLength() == arrSize + 3);
    assert(mutableListSeq2.get(2) == 10);

    // Test concat
    MutableListSequence<int> otherArrSeq(arr, arrSize);
    auto concatSeq = mutableListSeq2.concat(&otherArrSeq);
    assert(concatSeq->getLength() == arrSize * 2 + 3);
    assert(concatSeq->getLast() == 5);

    std::cout << "TEST 8 PASSED!" << std::endl;
}








