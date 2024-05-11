#pragma once

#include "MutableSequence.h"
#include "DynamicArray.h"


template<class T>
class MutableArraySequence : public MutableSequence<T> {
private:
    DynamicArray<T> base;

public:
    MutableArraySequence() : base{DynamicArray<T>()} {}

    MutableArraySequence(T *items, int length) : base{DynamicArray<T>(items, length)} {}

    MutableArraySequence(const DynamicArray<T> array) : base{DynamicArray<T>(array)} {}

    T getFirst() const override {
        return base.get(0);
    }

    T getLast() const override {
        return base.get(base.getSize() - 1);
    }

    T get(int index) const override {
        return base.get(index);
    }

    MutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.getSize() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.get(i);
        }
        return new MutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.getSize();
    }

    void append(const T item) override {
        base.setSize(base.getSize() + 1);
        base.set(base.getSize() - 1, item);
    }

    void prepend(const T item) override {
        base.setSize(base.getSize() + 1);
        for (int i = base.getSize() - 1; i > 0; --i) {
            base.set(i, base.get(i - 1));
        }
        base.set(0, item);
    }

    void insertAt(int index, const T item) override {
        base.setSize(base.getSize() + 1);
        for (int i = base.getSize() - 1; i > index; --i) {
            base.set(i, base.get(i - 1));
        }
        base.set(index, item);
    }

    MutableSequence<T> *concat(MutableSequence<T> *sequence) override {
        DynamicArray<T> newArray;
        newArray.setSize(base.getSize() + sequence->getLength());
        for (int i = 0; i < base.getSize(); ++i) {
            newArray.set(i, base.get(i));
        }
        for (int i = 0; i < sequence->getLength(); ++i) {
            newArray.set(i + base.getSize(), sequence->get(i));
        }
        return new MutableArraySequence<T>(newArray);
    }

};
