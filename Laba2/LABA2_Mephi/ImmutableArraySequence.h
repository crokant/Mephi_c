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
        return base.get_by_index(0);
    }

    const T &getLast() const override {
        return base.get_by_index(base.get_size() - 1);
    }

    const T &get(int index) const override {
        return base.get_by_index(index);
    }

    ImmutableArraySequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= base.get_size() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        T *subArray = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; ++i) {
            subArray[i - startIndex] = base.get_by_index(i);
        }
        return new ImmutableArraySequence<T>(subArray, endIndex - startIndex + 1);
    }

    int getLength() const override {
        return base.get_size();
    }

    ImmutableArraySequence<T> *append(const T item) const override {
        DynamicArray<T> newArray(base);
        newArray.set_size(newArray.get_size() + 1);
        newArray.insert_at(newArray.get_size() - 1, item);
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableArraySequence<T> *prepend(const T item) const override {
        DynamicArray<T> newArray;
        newArray.set_size(base.get_size() + 1);
        newArray.insert_at(0, item);
        for (int i = 0; i < base.get_size(); ++i) {
            newArray.insert_at(i + 1, base.get_by_index(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }


    ImmutableArraySequence<T> *insertAt(int index, const T item) const override {
        DynamicArray<T> newArray;
        newArray.set_size((base.get_size() + 1));
        for (int i = 0; i < index; ++i) {
            newArray.insert_at(i, base.get_by_index(i));
        }
        newArray.insert_at(index, item);
        for (int i = index; i < base.get_size(); ++i) {
            newArray.insert_at(i + 1, base.get_by_index(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }

    ImmutableArraySequence<T> *concat(ImmutableSequence<T> *sequence) const override {
        DynamicArray<T> newArray;
        newArray.set_size(base.get_size() + sequence->getLength());
        for (int i = 0; i < base.get_size(); ++i) {
            newArray.insert_at(i, base.get_by_index(i));
        }
        for (int i = 0; i < sequence->getLength(); ++i) {
            newArray.insert_at(i + base.get_size(), sequence->get(i));
        }
        return new ImmutableArraySequence<T>(newArray);
    }
};
