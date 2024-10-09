#pragma once

#include <stdexcept>
#include "SharedPtr.h"
#include "WeakPtr.h"
#include "UniquePtr.h"

template<typename T>
class Node {
public:
    T data;
    WeakPtr<Node<T>> left;
    SharedPtr<Node<T>> right;

    explicit Node(const T &value) : data(value), left(), right(nullptr) {}
};

template<class T>
class SmartList {
private:
    SharedPtr<Node<T>> first;
    SharedPtr<Node<T>> last;
    int size;

    void destroyList() {
        first.reset();
        last.reset();
        size = 0;
    }

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }

public:
    SmartList() : first(nullptr), last(nullptr), size(0) {}

    SmartList(T *items, int size) : first(nullptr), last(nullptr), size(0) {
        for (int i = 0; i < size; ++i) {
            append(items[i]);
        }
    }

    SmartList(const SmartList<T> &list) : first(nullptr), last(nullptr), size(0) {
        *this = list;
    }

    ~SmartList() {
        destroyList();
    }

    T &getFirst() const {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        return first->data;
    }

    T &getLast() const {
        if (!last) {
            throw std::out_of_range("ListIsEmpty");
        }
        return last->data;
    }

    T &getByIndex(int index) const {
        checkIndex(index);
        if (index < size / 2) {
            SharedPtr<Node<T>> temp = first;
            for (int i = 0; i < index; ++i) {
                temp = temp->right;
            }
            return temp->data;
        } else {
            WeakPtr<Node<T>> temp = WeakPtr(last);
            for (int i = size - 1; i > index; --i) {
                temp = temp->left;
            }
            return temp->data;
        }
    }

    UniquePtr<SmartList<T>> getSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        UniquePtr<SmartList<T>> sublist = UniquePtr<SmartList<T>>(new SmartList<T>);
        SharedPtr<Node<T>> temp = first;
        for (int i = 0; i < startIndex; ++i) {
            temp = temp->right;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
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
            first = last = newNode;
        } else {
            last->right = newNode;
            newNode->left = last;
            last = newNode;
        }
        size++;
    }

    void prepend(const T &value) {
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>(value));
        if (!first) {
            first = last = newNode;
        } else {
            first->left = newNode;
            newNode->right = first;
            first = newNode;
        }
        size++;
    }

    void insertAt(int index, const T &value) {
        checkIndex(index);
        if (index == size) {
            append(value);
        } else {
            SharedPtr<Node<T>> temp = first;
            for (int i = 0; i < index - 1; ++i) {
                temp = temp->right;
            }
            SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>(value));
            newNode->right = temp->right;
            newNode->left = temp;
            if (temp) {
                temp->right->left = newNode;
            }
            temp->right = newNode;
            size++;
        }
    }

    UniquePtr<SmartList<T>> concatenate(const SmartList<T> &other) const {
        UniquePtr<SmartList<T>> newList = UniquePtr<SmartList<T>>(new SmartList<T>);
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
