#pragma once

#include "ImmutableSequence.h"
#include "LinkedList.h"


template<class T>
class ImmutableListSequence : public ImmutableSequence<T> {
private:
    LinkedList<T> base;

public:
    ImmutableListSequence() : base{LinkedList<T>()} {}

    ImmutableListSequence(T *items, int size) : base{LinkedList(items, size)} {}

    ImmutableListSequence(const LinkedList<T> list) : base{list} {}

    const T &getFirst() const override {
        return base.getFirst();
    }

    const T &getLast() const override {
        return base.getLast();
    }

    const T &get(int index) const override {
        return base.getByIndex(index);
    }

    ImmutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        return new ImmutableListSequence(*base.getSubList(startIndex, endIndex));
    }

    int getLength() const override {
        return base.getLength();
    }

    ImmutableListSequence<T> *append(const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.append(item);
        return newSequence;
    }

    ImmutableListSequence<T> *prepend(const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.prepend(item);
        return newSequence;
    }

    ImmutableListSequence<T> *insertAt(int index, const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.insertAt(index, item);
        return newSequence;
    }

    ImmutableListSequence<T> *concat(ImmutableSequence<T> *sequence) const override {
        LinkedList<T> newList;
        for (int i = 0; i < base.getLength(); ++i) {
            newList.append(base.getByIndex(i));
        }
        for (int i = 0; i < sequence->getLength(); ++i) {
            newList.append(sequence->get(i));
        }
        return new ImmutableListSequence<T>(newList);
    }
    /*
    ImmutableListSequence<T> *concat(ImmutableSequence<T> *sequence) const override {
        LinkedList<T> newList(sequence);
        LinkedList<T> newBase = *base.concatenate(newList);
        return new ImmutableListSequence<T>(newBase);
    }
    */
};
