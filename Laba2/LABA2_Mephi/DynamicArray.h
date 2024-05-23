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
        T *newData = new T[capacity];
        if (capacity < size) throw std::invalid_argument("NegativeResize");
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        allocatedMemory = capacity;
    }

public:
    DynamicArray() : data{nullptr}, allocatedMemory{5}, size{0} {}

    DynamicArray(int length) : allocatedMemory{length + 5}, size{0} {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length];
    }

    DynamicArray(const T *items, int length) : allocatedMemory{length + 5}, size{length} {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length];
        for (int i = 0; i < length; ++i) {
            this->data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> &array) : allocatedMemory{array.allocatedMemory + 5}, size{array.size} {
        this->data = new T[array.allocatedMemory];
        for (int i = 0; i < array.size; ++i) {
            this->data[i] = array.data[i];
        }
    }

    DynamicArray(const MutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                       size{sequence->getLength()} {
        this->data = new T[sequence->getLength()];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    DynamicArray(const ImmutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                         size{sequence->getLength()} {
        this->data = new T[sequence->getLength()];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T &get_by_index(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    void insert_at(int index, const T &value) {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        data[index] = value;
    }

    int get_size() const {
        return size;
    }

    void set_size(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("NegativeSize");
        }
        if (newSize > allocatedMemory) {
            resize(newSize + 5);
        }
        size = newSize;
    }
};
