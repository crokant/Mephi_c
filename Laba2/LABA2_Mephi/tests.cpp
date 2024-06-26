#include <iostream>
#include "tests.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include <cassert>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"


//test dynamic array
void test_dynamic_array() {
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = 5;

    DynamicArray<int> dynamicArr(arr, arrSize);
    assert(dynamicArr.getSize() == arrSize);
    for (int i = 0; i < arrSize; i++) {
        assert(dynamicArr.getByIndex(i) == arr[i]);
    }

    int newSize = 10;
    int newValue = 100;

    dynamicArr.setSize(newSize);
    assert(dynamicArr.getSize() == newSize);

    dynamicArr.insertAt(7, newValue);
    assert(dynamicArr.getByIndex(7) == newValue);
    std::cout << GREEN << "TEST 1 PASSED!" << RESET << std::endl;

}

//test linked list
void test_linked_list() {
    //test default constructor
    LinkedList<int> linkedList1;
    assert(linkedList1.getLength() == 0);

    //test constructor with array
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    LinkedList<int> linkedList2(arr, arrSize);
    assert(linkedList2.getLength() == arrSize);
    assert(linkedList2.getFirst() == 1);
    assert(linkedList2.getLast() == 5);
    assert(linkedList2.getByIndex(2) == 3);

    //test append prepend
    linkedList1.append(10);
    linkedList1.prepend(20);
    linkedList1.append(30);
    assert(linkedList1.getLength() == 3);
    assert(linkedList1.getFirst() == 20);
    assert(linkedList1.getLast() == 30);
    assert(linkedList1.getByIndex(1) == 10);
    linkedList1.prepend(5);
    assert(linkedList1.getLength() == 4);
    assert(linkedList1.getFirst() == 5);

    //test insert at
    linkedList1.insertAt(2, 15);
    assert(linkedList1.getLength() == 5);
    assert(linkedList1.getByIndex(2) == 15);
    assert(linkedList1.getLast() == 30);

    //random sublist
    auto sublist1 = linkedList1.getSubList(1, 3);
    assert(sublist1->getLength() == 3);
    assert(sublist1->getFirst() == 20);
    //first element
    auto sublist2 = linkedList1.getSubList(0, 0);
    assert(sublist2->getLength() == 1);
    assert(sublist2->getFirst() == 5);
    //empty linked list
    auto sublist3 = linkedList1.getSubList(4, 3);
    assert(sublist3->getLength() == 0);
    //last element
    auto sublist4 = linkedList1.getSubList(4, 4);
    assert(sublist4->getLength() == 1);
    assert(sublist4->getFirst() == 30);


    std::cout << GREEN << "TEST 2 PASSED!" << RESET << std::endl;
}

//test immutable array sequence
void test_immutable_array_sequence() {
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

    std::cout << GREEN << "TEST 3 PASSED!" << RESET << std::endl;
}

//test mutable array sequence
void test_mutable_array_sequence() {
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
    mutableArraySeq2.concat(&otherArraySeq);
    assert(mutableArraySeq2.getLast() == 9);
    assert(mutableArraySeq2.getLength() == arrSize + arr2Size + 3);

    std::cout << GREEN << "TEST 4 PASSED!" << RESET << std::endl;
}

void test_immutable_linked_list() {
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
    std::cout << GREEN << "TEST 5 PASSED!" << RESET << std::endl;
}

void test_mutable_linked_list() {
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
    mutableListSeq2.concat(&otherArrSeq);
    assert(mutableListSeq2.getLength() == arrSize * 2 + 3);
    assert(mutableListSeq2.getLast() == 5);

    std::cout << GREEN << "TEST 6 PASSED!" << RESET << std::endl;
}








