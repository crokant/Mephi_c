#include <iostream>
#include <cassert>
#include "SmartList.h"
#include "SmartListSequence.h"

void testSmartListSequence() {
    SmartListSequence<int> sequence;
    assert(sequence.getLength() == 0);

    int items[] = {1, 2, 3, 4, 5};
    SmartListSequence<int> sequenceWithItems(items, 5);
    assert(sequenceWithItems.getLength() == 5);
    assert(sequenceWithItems.getFirst() == 1);
    assert(sequenceWithItems.getLast() == 5);

    assert(sequenceWithItems.get(0) == 1);
    assert(sequenceWithItems.get(1) == 2);
    assert(sequenceWithItems.get(4) == 5);

    UniquePtr<SmartListSequence<int>> subSequence = UniquePtr(sequenceWithItems.getSubSequence(1, 3));
    assert(subSequence->getLength() == 3);
    assert(subSequence->get(0) == 2);
    assert(subSequence->get(1) == 3);
    assert(subSequence->get(2) == 4);
   // delete subSequence;

    sequence.append(10);
    assert(sequence.getLength() == 1);
    assert(sequence.getFirst() == 10);
    assert(sequence.getLast() == 10);

    sequence.prepend(5);
    assert(sequence.getLength() == 2);
    assert(sequence.getFirst() == 5);
    assert(sequence.getLast() == 10);

    sequence.insertAt(1, 7);
    assert(sequence.getLength() == 3);
    assert(sequence.get(0) == 5);
    assert(sequence.get(1) == 7);
    assert(sequence.get(2) == 10);

    SmartListSequence<int> anotherSequence;
    anotherSequence.append(20);
    anotherSequence.append(30);

    sequence.concat(&anotherSequence);
    assert(sequence.getLength() == 5);
    assert(sequence.get(3) == 20);
    assert(sequence.get(4) == 30);

    std::cout << "All tests for SmartListSequence passed!" << std::endl;
}

void testLinkedList() {
    SmartList<int> list;

    assert(list.getLength() == 0);
    try {
        list.getFirst();
        assert(false);
    } catch (const std::out_of_range&) {}

    try {
        list.getLast();
        assert(false);
    } catch (const std::out_of_range&) {}

    list.append(1);
    assert(list.getLength() == 1);
    assert(list.getFirst() == 1);
    assert(list.getLast() == 1);

    list.append(2);
    assert(list.getLength() == 2);
    assert(list.getFirst() == 1);
    assert(list.getLast() == 2);

    list.append(3);
    assert(list.getLength() == 3);
    assert(list.getFirst() == 1);
    assert(list.getLast() == 3);

    assert(list.getByIndex(0) == 1);
    assert(list.getByIndex(1) == 2);
    assert(list.getByIndex(2) == 3);

    try {
        list.getByIndex(3);
        assert(false);
    } catch (const std::out_of_range&) {}

    list.prepend(0);
    assert(list.getLength() == 4);
    assert(list.getFirst() == 0);
    assert(list.getLast() == 3);

    list.insertAt(2, 1);
    assert(list.getByIndex(2) == 1);
    assert(list.getLength() == 5);

    assert(list.getByIndex(0) == 0);
    assert(list.getByIndex(1) == 1);
    assert(list.getByIndex(2) == 1);
    assert(list.getByIndex(3) == 2);
    assert(list.getByIndex(4) == 3);

    UniquePtr<SmartList<int>> subList = UniquePtr(list.getSubList(1, 3)); // Создаем подпоследовательность с индексами от 1 до 3
    assert(subList->getLength() == 3);
    assert(subList->getByIndex(0) == 1); // 1
    assert(subList->getByIndex(1) == 1); // 1
    assert(subList->getByIndex(2) == 2); // 2


    list = SmartList<int>();
    assert(list.getLength() == 0);


    list.append(1);
    list.append(2);
    SmartList<int> otherList;
    otherList.append(3);
    otherList.append(4);

    UniquePtr<SmartList<int>> combinedList = UniquePtr(list.concatenate(otherList));
    assert(combinedList->getLength() == 4);
    assert(combinedList->getByIndex(0) == 1);
    assert(combinedList->getByIndex(1) == 2);
    assert(combinedList->getByIndex(2) == 3);
    assert(combinedList->getByIndex(3) == 4);

    //delete combinedList;

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testLinkedList();
    testSmartListSequence();
    return 0;
}
