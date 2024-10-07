#include <iostream>
#include <cassert>
#include "SmartList.h"

void testLinkedList() {
    // Создание списка
    SmartList<int> list;

    // Проверка, что список пуст
    assert(list.getLength() == 0);
    try {
        list.getFirst();
        assert(false); // Это не должно сработать, список пуст
    } catch (const std::out_of_range&) {}

    try {
        list.getLast();
        assert(false); // Это не должно сработать, список пуст
    } catch (const std::out_of_range&) {}

    // Добавление элементов
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

    // Проверка доступа по индексу
    assert(list.getByIndex(0) == 1);
    assert(list.getByIndex(1) == 2);
    assert(list.getByIndex(2) == 3);

    // Проверка исключения для неверного индекса
    try {
        list.getByIndex(3);
        assert(false); // Это не должно сработать
    } catch (const std::out_of_range&) {}

    // Добавление в начало
    list.prepend(0);
    assert(list.getLength() == 4);
    assert(list.getFirst() == 0);
    assert(list.getLast() == 3);

    // Вставка по индексу
    list.insertAt(2, 1);
    assert(list.getByIndex(2) == 1);
    assert(list.getLength() == 5);

    // Проверка списка
    assert(list.getByIndex(0) == 0);
    assert(list.getByIndex(1) == 1);
    assert(list.getByIndex(2) == 1);
    assert(list.getByIndex(3) == 2);
    assert(list.getByIndex(4) == 3);

    // Создание подпоследовательности
    SmartList<int> *subList = list.getSubList(1, 3); // Создаем подпоследовательность с индексами от 1 до 3
    assert(subList->getLength() == 3);
    assert(subList->getByIndex(0) == 1); // 1
    assert(subList->getByIndex(1) == 1); // 1
    assert(subList->getByIndex(2) == 2); // 2

    delete subList; // Освобождение памяти после создания подпоследовательности

    // Удаление элементов
    list = SmartList<int>(); // Очистка списка
    assert(list.getLength() == 0);

    // Проверка объединения списков
    list.append(1);
    list.append(2);
    SmartList<int> otherList;
    otherList.append(3);
    otherList.append(4);

    SmartList<int> *combinedList = list.concatenate(otherList);
    assert(combinedList->getLength() == 4);
    assert(combinedList->getByIndex(0) == 1);
    assert(combinedList->getByIndex(1) == 2);
    assert(combinedList->getByIndex(2) == 3);
    assert(combinedList->getByIndex(3) == 4);

    delete combinedList; // Освобождение памяти после объединения

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testLinkedList();
    return 0;
}
