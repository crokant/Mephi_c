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

    T &getFirst() const override {
        return base.get_by_index(0);
    }

    T &getLast() const override {
        return base.get_by_index(base.get_size() - 1);
    }

    T &get(int index) const override {
        return base.get_by_index(index);
    }

    MutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.get_size() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.get_by_index(i);
        }
        return new MutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.get_size();
    }

    void append(const T item) override {
        base.set_size(base.get_size() + 1);
        base.insert_at(base.get_size() - 1, item);
    }

    void prepend(const T item) override {
        base.set_size(base.get_size() + 1);
        for (int i = base.get_size() - 1; i > 0; --i) {
            base.insert_at(i, base.get_by_index(i - 1));
        }
        base.insert_at(0, item);
    }

    void insertAt(int index, const T item) override {
        base.set_size(base.get_size() + 1);
        for (int i = base.get_size() - 1; i > index; --i) {
            base.insert_at(i, base.get_by_index(i - 1));
        }
        base.insert_at(index, item);
    }

    void concat(MutableSequence<T> *sequence) override {
        int originalSize = base.get_size();
        int newSize = originalSize + sequence->getLength();
        base.set_size(newSize);
        for (int i = 0; i < sequence->getLength(); ++i) {
            base.insert_at(originalSize + i, sequence->get(i));
        }
    }
};
