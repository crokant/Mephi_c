#pragma once

#include "MutableSequence.h"
#include "LinkedList.h"


template<class T>
class MutableListSequence : public MutableSequence<T> {
private:
    LinkedList<T> base;

public:
    MutableListSequence() : base{LinkedList<T>()} {}

    MutableListSequence(T *items, int size) : base{LinkedList<T>(items, size)} {}

    MutableListSequence(const LinkedList<T> list) : base{list} {}

    T &getFirst() override {
        return base.get_first();
    }

    T &getLast() override {
        return base.get_last();
    }

    T &get(int index) override {
        return base.get_by_index(index);
    }

    MutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        return new MutableListSequence<T>(*base.get_sub_list(startIndex, endIndex));
    }

    int getLength() const override {
        return base.get_length();
    }

    void append(const T item) override {
        base.list_append(item);
    }

    void prepend(const T item) override {
        base.list_prepend(item);
    }

    void insertAt(int index, const T item) override {
        base.insert_at(index, item);
    }

    void concat(MutableSequence<T> *sequence) override {
        for (int i = 0; i < sequence->getLength(); ++i) {
            base.list_append(sequence->get(i));
        }
    }
};