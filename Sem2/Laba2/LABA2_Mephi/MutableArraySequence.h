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

    const T &getFirst() const override {
        return base.getByIndex(0);
    }

    const T &getLast() const override {
        return base.getByIndex(base.getSize() - 1);
    }

    const T &get(int index) const override {
        return base.getByIndex(index);
    }

    MutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.getSize() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.getByIndex(i);
        }
        return new MutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.getSize();
    }

    void append(const T item) override {
        base.insertAt(base.getSize(), item);
    }

    void prepend(const T item) override {
        base.insertAt(0, item);
    }

    void insertAt(int index, const T item) override {
        base.insertAt(index, item);
    }

    void set(int index, const T &value) {
        if (index < 0 || index >= base.getSize()) {
            throw std::out_of_range("IndexOutOfRange");
        }
        base.set(index, value);
    }

    void concat(MutableSequence<T> *sequence) override {
        int oldSize = base.getSize();
        for (int i = 0; i < sequence->getLength(); ++i) {
            base.insertAt(i + oldSize, sequence->get(i));
        }
    }
};
