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

    T getFirst() const override {
        return base.get_first();
    }

    T getLast() const override {
        return base.get_last();
    }

    T get(int index) const override {
        return base.get_by_index(index);
    }

    ImmutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        return new ImmutableListSequence(*base.get_sub_list(startIndex, endIndex));
    }

    int getLength() const override {
        return base.get_length();
    }

    ImmutableListSequence<T> *append(const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.list_append(item);
        return newSequence;
    }

    ImmutableListSequence<T> *prepend(const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.list_prepend(item);
        return newSequence;
    }

    ImmutableListSequence<T> *insertAt(int index, const T item) const override {
        auto *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.insert_at(index, item);
        return newSequence;
    }

    ImmutableListSequence<T>* concat(ImmutableSequence<T>* sequence) const override {
        LinkedList<T> newList(sequence);
        LinkedList<T> newBase = *base.concatenate(newList);
        return new ImmutableListSequence<T>(newBase);
    }
};
