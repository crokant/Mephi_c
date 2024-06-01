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
        return base.getFirst();
    }

    T &getLast() override {
        return base.getLast();
    }

    T &get(int index) override {
        return base.getByIndex(index);
    }

    MutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        return new MutableListSequence<T>(*base.getSubList(startIndex, endIndex));
    }

    int getLength() const override {
        return base.getLength();
    }

    void append(const T item) override {
        base.append(item);
    }

    void prepend(const T item) override {
        base.prepend(item);
    }

    void insertAt(int index, const T item) override {
        base.insertAt(index, item);
    }

    void concat(MutableSequence<T> *sequence) override {
        for (int i = 0; i < sequence->getLength(); ++i) {
            base.append(sequence->get(i));
        }
    }
};
