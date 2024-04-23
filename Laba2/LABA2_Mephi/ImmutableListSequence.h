#pragma once

#include "ImmutableSequence.h"
#include "LinkedList.h"


template<class T>
class ImmutableListSequence : ImmutableSequence<T> {
private:
    LinkedList<T> base;

public:
    ImmutableListSequence() : base{LinkedList<T>()} {}

    ImmutableListSequence(T *items, int size) : base{LinkedList(items, size)} {}

    ImmutableListSequence(const LinkedList<T> list) : base{list} {}

    T getFirst() const override {
        return base.getFirst();
    }

    T getLast() const override {
        return base.getLast();
    }

    T get(int index) const override {
        return base.get(index);
    }

    ImmutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        return new ImmutableListSequence(*base.getSubList(startIndex, endIndex));
    }

    int getLength() const override {
        return base.getLength();
    }

    ImmutableListSequence<T> *append(const T item) const override {
        ImmutableListSequence<T> *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.append(item);
        return newSequence;
    }

    ImmutableListSequence<T> *prepend(const T item) const override {
        ImmutableListSequence<T> *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.prepend(item);
        return newSequence;
    }

    ImmutableListSequence<T> *insertAt(int index, const T item) const override {
        ImmutableListSequence<T> *newSequence = new ImmutableListSequence<T>(base);
        newSequence->base.insert(index, item);
        return newSequence;
    }

    ImmutableListSequence<T> *concat(ImmutableSequence<T> *list) const override {
        auto newList = new LinkedList<T>(base);
        auto otherList = dynamic_cast<ImmutableListSequence<T> *>(list);
        if (!otherList)
            throw std::invalid_argument("Invalid type for concatenation.");
        newList->concatenate(otherList->base);
        return new ImmutableListSequence<T>(*newList);
    }

};
