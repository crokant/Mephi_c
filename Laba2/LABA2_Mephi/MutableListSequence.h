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

    T getFirst() const override {
        return base.getFirst();
    }

    T getLast() const override {
        return base.getLast();
    }

    T get(int index) const override {
        return base.get(index);
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
        base.insert(index, item);
    }
//сделать mutable
    MutableListSequence<T> *concat(MutableSequence<T> *list) override {
        auto newList = new LinkedList<T>(base);
        auto otherList = dynamic_cast<MutableListSequence<T> *>(list);
        if (!otherList)
            throw std::invalid_argument("Invalid type for concatenation.");
        newList->concatenate(otherList->base);
        return new MutableListSequence<T>(*newList);
    }

};