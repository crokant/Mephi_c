#pragma once

#include "MutableSequence.h"
#include "ImmutableSequence.h"

#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    T *data;
    int allocatedMemory;
    int size;

    void resize(int capacity) {
        if (capacity < size) throw std::invalid_argument("NegativeResize");
        T *newData = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        allocatedMemory = capacity;
    }

public:
    DynamicArray() : data{new T[5]}, allocatedMemory{5}, size{0} {}

    DynamicArray(int length) : allocatedMemory{length + 5}, size{length} {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length + 5];
    }

    DynamicArray(const T *items, int length) : allocatedMemory{length + 5}, size{length} {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length + 5];
        for (int i = 0; i < length; ++i) {
            this->data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> &array) : allocatedMemory{array.allocatedMemory}, size{array.size} {
        this->data = new T[array.allocatedMemory];
        for (int i = 0; i < array.size; ++i) {
            this->data[i] = array.data[i];
        }
    }

    DynamicArray(const MutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                       size{sequence->getLength()} {
        this->data = new T[sequence->getLength() + 5];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    DynamicArray(const ImmutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                         size{sequence->getLength()} {
        this->data = new T[sequence->getLength() + 5];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T &getByIndex(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    void insertAt(int index, const T &value) {
        if (index < 0 || index > size) throw std::out_of_range("IndexOutOfRange");
        if (size + 1 > allocatedMemory) {
            resize(allocatedMemory + 5);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    int getSize() const {
        return size;
    }

    void setSize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("NegativeSize");
        }
        if (newSize > allocatedMemory) {
            resize(newSize + 5);
        }
        size = newSize;
    }
};
