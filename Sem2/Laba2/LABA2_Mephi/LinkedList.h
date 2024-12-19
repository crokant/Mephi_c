#pragma once

#include "ImmutableSequence.h"
#include "MutableSequence.h"

#include <stdexcept>


template<typename T>
class Node {
public:
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(const T &value) : data{value}, left{nullptr}, right{nullptr} {}
};

template<class T>
class LinkedList {
private:
    Node<T> *first;
    Node<T> *last;
    int size;

    void destroyList() {
        Node<T> *temp = first;
        while (temp) {
            Node<T> *next = temp->right;
            delete temp;
            temp = next;
        }
        first = last = nullptr;
        size = 0;
    }

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }

public:
    LinkedList() : first{nullptr}, last{nullptr}, size{0} {}

    LinkedList(T *items, int size) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < size; ++i) {
            append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : first{nullptr}, last{nullptr}, size{0} {
        *this = list;
    }

    LinkedList(const MutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            append(sequence->get(i));
        }
    }


    LinkedList(const ImmutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            append(sequence->get(i));
        }
    }

    ~LinkedList() {
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
        Node<T> *temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->right;
        }
        return temp->data;
    }

    LinkedList<T> *getSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto *sublist = new LinkedList<T>;
        Node<T> *temp = first;
        for (int i = 0; i < startIndex; ++i) {
            temp = temp->right;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
            sublist->append(temp->data);
            temp = temp->right;
        }
        return sublist;
    }

    int getLength() const {
        return size;
    }

    void append(const T &value) {
        auto *newNode = new Node<T>(value);
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
        auto *newNode = new Node<T>(value);
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
        if (index == 0) {
            prepend(value);
        } else if (index == size) {
            append(value);
        } else {
            Node<T> *temp = first;
            for (int i = 0; i < index - 1; ++i) {
                temp = temp->right;
            }
            auto *newNode = new Node<T>(value);
            newNode->right = temp->right;
            newNode->left = temp;
            temp->right->left = newNode;
            temp->right = newNode;
            size++;
        }
    }

    LinkedList<T> *concatenate(const LinkedList<T> &other) const {
        auto newList = new LinkedList<T>;
        Node<T> *temp = first;
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

    void removeFirst() {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        Node<T> *temp = first;
        first = first->right;
        if (first) {
            first->left = nullptr;
        } else {
            last = nullptr;
        }
        delete temp;
        size--;
    }

    void removeLast() {
        if (!last) {
            throw std::out_of_range("ListIsEmpty");
        }
        Node<T> *temp = last;
        last = last->left;
        if (last) {
            last->right = nullptr;
        } else {
            first = nullptr;
        }
        delete temp;
        size--;
    }

    void removeByIndex(int index) {
        checkIndex(index);
        if (index == 0) {
            removeFirst();
        } else if (index == size - 1) {
            removeLast();
        } else {
            Node<T> *temp = first;
            for (int i = 0; i < index; ++i) {
                temp = temp->right;
            }
            temp->left->right = temp->right;
            temp->right->left = temp->left;
            delete temp;
            size--;
        }
    }

    LinkedList<T> &operator=(const LinkedList<T> &list) {
        if (this != &list) {
            destroyList();
            Node<T> *temp = list.first;
            while (temp) {
                append(temp->data);
                temp = temp->right;
            }
        }
        return *this;
    }
};
