#pragma once

#include "SharedPtr.h"
#include "UniquePtr.h"

#include <stdexcept>

template<typename T>
class Node {
public:
    T data;
    SharedPtr<Node<T>> right;

    explicit Node(const T &value) : data(value), right(nullptr) {}
};

template<class T>
class SmartList {
private:
    SharedPtr<Node<T>> first;
    int size;

    void destroyList() {
        first.reset();
        size = 0;
    }

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }

public:
    SmartList() : first(nullptr), size(0) {}

    SmartList(T *items, int size) : first(nullptr), size(0) {
        for (int i = 0; i < size; ++i) {
            append(items[i]);
        }
    }

    SmartList(const SmartList<T> &list) : first(nullptr), size(0) {
        *this = list;
    }

    ~SmartList() {
        destroyList();
    }

    const T &getFirst() const {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        return first->data;
    }

    const T &getLast() const {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        SharedPtr<Node<T>> temp = first;
        while (temp->right) {
            temp = temp->right;
        }
        return temp->data;
    }

    const T &getByIndex(int index) const {
        checkIndex(index);
        SharedPtr<Node<T>> temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->right;
        }
        return temp->data;
    }

    SharedPtr<SmartList<T>> getSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        SharedPtr<SmartList<T>> sublist = SharedPtr<SmartList<T>>(new SmartList<T>);
        SharedPtr<Node<T>> temp = first;
        for (int i = 0; i < startIndex; ++i) {
            temp = temp->right;
        }
        for (int i = startIndex; i <= endIndex && temp; ++i) {
            sublist->append(temp->data);
            temp = temp->right;
        }
        return sublist;
    }

    [[nodiscard]] int getLength() const {
        return size;
    }

    void append(const T &value) {
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>(value));
        if (!first) {
            first = newNode;
        } else {
            SharedPtr<Node<T>> temp = first;
            while (temp->right) {
                temp = temp->right;
            }
            temp->right = newNode;
        }
        size++;
    }

    void prepend(const T &value) {
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>(value));
        newNode->right = first;
        first = newNode;
        size++;
    }

    void insertAt(int index, const T &value) {
        checkIndex(index);
        SharedPtr<Node<T>> temp = first;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->right;
        }
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>(value));
        newNode->right = temp->right;
        temp->right = newNode;
        size++;
    }

    SharedPtr<SmartList<T>> concatenate(const SmartList<T> &other) const {
        SharedPtr<SmartList<T>> newList = SharedPtr<SmartList<T>>(new SmartList<T>);
        SharedPtr<Node<T>> temp = first;
        while (temp) {
            newList->append(temp->data);
            temp = temp->right;
        }
        temp = other.first;
        while (temp) {
            newList->append(temp->data);
            temp = temp->right;
        }
        return newList;
    }

    SmartList<T> &operator=(const SmartList<T> &list) {
        if (this != &list) {
            destroyList();
            SharedPtr<Node<T>> temp = list.first;
            while (temp) {
                append(temp->data);
                temp = temp->right;
            }
        }
        return *this;
    }
};
