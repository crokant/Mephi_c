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

    T getFirst() const override {
        return base.get(0);
    }

    T getLast() const override {
        return base.get(base.getSize() - 1);
    }

    T get(int index) const override {
        return base.get(index);
    }

    ImmutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.getSize() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.get(i);
        }
        return new ImmutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.getSize();
    }

    ImmutableArraySequence<T> *append(const T item) const override {
        DynamicArray<T> newArray(base);
        newArray.setSize(newArray.getSize() + 1);
        newArray.set(newArray.getSize() - 1, item);
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableArraySequence<T> *prepend(const T item) const override {
        DynamicArray<T> newArray;
        newArray.setSize(base.getSize() + 1);
        newArray.set(0, item);
        for (int i = 0; i < base.getSize(); ++i) {
            newArray.set(i + 1, base.get(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }


    ImmutableArraySequence<T> *insertAt(int index, const T item) const override {
        DynamicArray<T> newArray;
        newArray.setSize((base.getSize() + 1));
        for (int i = 0; i < index; ++i) {
            newArray.set(i, base.get(i));
        }
        newArray.set(index, item);
        for (int i = index; i < base.getSize(); ++i) {
            newArray.set(i + 1, base.get(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableSequence<T> *concat(ImmutableSequence<T> *sequence) const override {
        DynamicArray<T> newArray;
        newArray.setSize(base.getSize() + sequence->getLength());
        for (int i = 0; i < base.getSize(); ++i) {
            newArray.set(i, base.get(i));
        }
        for (int i = 0; i < sequence->getLength(); ++i) {
            newArray.set(i + base.getSize(), sequence->get(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }


};
