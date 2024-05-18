#pragma once

#include <stdexcept>


template<typename T>
class DynamicArray {
private:
    T *data;
    int allocatedMemory;
    int size;
    //size_t size
    //size_t capacity;
    //удалить capacity
    void resize(int capacity) {
        T *newData = new T[capacity];
        //capacity < size
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        allocatedMemory = capacity;
    }

public:
    DynamicArray() : data(nullptr), allocatedMemory(0), size(0) {}

    DynamicArray(int length) : allocatedMemory(length), size(0) {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length];
    }

    DynamicArray(const T *items, int length) : allocatedMemory(length), size(length) {
        if (length < 0) throw std::invalid_argument("NegativeLength");
        this->data = new T[length];
        for (int i = 0; i < length; ++i) {
            this->data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> &array) : allocatedMemory(array.allocatedMemory), size(array.size) {
        this->data = new T[array.allocatedMemory];
        for (int i = 0; i < array.size; ++i) {
            this->data[i] = array.data[i];
        }
    }
    //конструктор копирующий sequence добавить

    ~DynamicArray() {
        delete[] data;
    }

    T get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    void set(int index, const T &value) {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        data[index] = value;
    }

    int getSize() const {
        return size;
    }

    void setSize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("NegativeSize");
        }
        if (newSize > allocatedMemory) {
            resize(newSize);
        }
        size = newSize;
    }
};
