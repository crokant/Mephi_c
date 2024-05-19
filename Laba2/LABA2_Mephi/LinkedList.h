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
            list_append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : first{nullptr}, last{nullptr}, size{0} {
        *this = list;
    }

    LinkedList(const MutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            list_append(sequence->get(i));
        }
    }


    LinkedList(const ImmutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            list_append(sequence->get(i));
        }
    }

    ~LinkedList() {
        destroyList();
    }

    T get_first() const {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        return first->data;
    }

    T get_last() const {
        if (!last) {
            throw std::out_of_range("ListIsEmpty");
        }
        return last->data;
    }

    T get_by_index(int index) const {
        checkIndex(index);
        Node<T> *temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->right;
        }
        return temp->data;
    }

    LinkedList<T> *get_sub_list(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex + 1);
        auto *sublist = new LinkedList<T>;
        Node<T> *temp = first;
        for (int i = 0; i < startIndex; ++i) {
            temp = temp->right;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
            sublist->list_append(temp->data);
            temp = temp->right;
        }
        return sublist;
    }

    int get_length() const {
        return size;
    }

    void list_append(const T &value) {
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

    void list_prepend(const T &value) {
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

    void insert_at(int index, const T &value) {
        checkIndex(index);
        if (index == 0) {
            list_prepend(value);
        } else if (index == size) {
            list_append(value);
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
        Node<T>* temp = first;
        while (temp) {
            newList->list_append(temp->data);
            temp = temp->right;
        }
        temp = other.first;
        while (temp) {
            newList->list_append(temp->data);
            temp = temp->right;
        }
        return newList;
    }

    LinkedList<T> &operator=(const LinkedList<T> &list) {
        if (this != &list) {
            destroyList();
            Node<T> *temp = list.first;
            while (temp) {
                list_append(temp->data);
                temp = temp->right;
            }
        }
        return *this;
    }

};
