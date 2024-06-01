#pragma once

#include "ImmutableSequence.h"
#include "DynamicArray.h"


template<class T>
class ImmutableArraySequence : public ImmutableSequence<T> {
private:
    const DynamicArray<T> base;

public:
    ImmutableArraySequence() : base{DynamicArray<T>()} {}

    ImmutableArraySequence(T *items, int length) : base{DynamicArray<T>(items, length)} {}

    ImmutableArraySequence(const DynamicArray<T> &array) : base{array} {}

    const T &getFirst() const override {
        return base.getByIndex(0);
    }

    const T &getLast() const override {
        return base.getByIndex(base.getSize() - 1);
    }

    const T &get(int index) const override {
        return base.getByIndex(index);
    }

    ImmutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.getSize() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.getByIndex(i);
        }
        return new ImmutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.getSize();
    }

    ImmutableArraySequence<T> *append(const T item) const override {
        DynamicArray<T> newArray(base);
        newArray.insertAt(newArray.getSize(), item);
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableArraySequence<T> *prepend(const T item) const override {
        DynamicArray<T> newArray(base);
        newArray.insertAt(0, item);
        return new ImmutableArraySequence<T>(newArray);
    }


    ImmutableArraySequence<T> *insertAt(int index, const T item) const override {
        DynamicArray<T> newArray(base);
        newArray.insertAt(index, item);
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableArraySequence<T> *concat(ImmutableSequence<T> *sequence) const override {
        DynamicArray<T> newArray;
        for (int i = 0; i < base.getSize(); ++i) {
            newArray.insertAt(i, base.getByIndex(i));
        }
        for (int i = 0; i < sequence->getLength(); ++i) {
            newArray.insertAt(i + base.getSize(), sequence->get(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }
};
