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

    explicit DynamicArray(int length) : allocatedMemory{length + 5}, size{length} {
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

    DynamicArray(DynamicArray<T> &&other) noexcept: data{other.data}, allocatedMemory{other.allocatedMemory},
                                                    size{other.size} {
        other.data = nullptr;
        other.allocatedMemory = 0;
        other.size = 0;
    }

    explicit DynamicArray(const MutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                                size{sequence->getLength()} {
        this->data = new T[sequence->getLength() + 5];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    explicit DynamicArray(const ImmutableSequence<T> *sequence) : allocatedMemory{sequence->getLength() + 5},
                                                                  size{sequence->getLength()} {
        this->data = new T[sequence->getLength() + 5];
        for (int i = 0; i < sequence->getLength(); ++i) {
            this->data[i] = sequence->get(i);
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            allocatedMemory = other.allocatedMemory;
            data = new T[allocatedMemory];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    bool operator==(const DynamicArray<T> &other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    T &operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    const T &operator[](int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    T &getByIndex(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }

    void add(const T &value) {
        if (size + 1 > allocatedMemory) {
            resize(allocatedMemory + 5);
        }
        data[size++] = value;
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

    void set(int index, const T &value) {
        if (index < 0 || index >= size) throw std::out_of_range("IndexOutOfRange");
        data[index] = value;
    }

    [[nodiscard]] int getSize() const {
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

    class Iterator {
    private:
        T *cur;
        size_t index;
        DynamicArray<T> *ptr;

    public:
        Iterator() : cur{nullptr}, index{0}, ptr{nullptr} {}

        Iterator(T *first, size_t index, DynamicArray<T> *self) : cur{first}, index{index}, ptr{self} {}

        Iterator(const Iterator &other) : cur{other.cur}, index{other.index}, ptr{other.ptr} {}

        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator operator+(difference_type n) const {
            if (index + n > ptr->size)
                throw std::out_of_range("Iterator out of working zone(+)");
            return Iterator(cur + n, index + n, ptr);
        }

        Iterator operator-(difference_type n) const {
            if (index < n)
                throw std::out_of_range("Iterator out of working zone(-)");
            return Iterator(cur - n, index - n, ptr);
        }

        difference_type operator-(const Iterator &other) const {
            return cur - other.cur;
        }

        Iterator &operator++() {
            if (index + 1 > ptr->size)
                throw std::out_of_range("Iterator out of working zone(++)");
            ++index;
            ++cur;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--() {
            if (index < 0)
                throw std::out_of_range("Iterator out of working zone(--)");
            --index;
            --cur;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator &operator+=(difference_type n) {
            if (index + n > ptr->size)
                throw std::out_of_range("Iterator out of working zone(+=)");
            index += n;
            cur += n;
            return *this;
        }

        Iterator &operator-=(difference_type n) {
            if (index < n)
                throw std::out_of_range("Iterator out of working zone(-=)");
            index -= n;
            cur -= n;
            return *this;
        }

        bool operator!=(const Iterator &it) const { return cur != it.cur; }

        bool operator==(const Iterator &it) const { return cur == it.cur; }

        bool operator<(const Iterator &it) const { return cur < it.cur; }

        bool operator<=(const Iterator &it) const { return cur <= it.cur; }

        bool operator>(const Iterator &it) const { return cur > it.cur; }

        bool operator>=(const Iterator &it) const { return cur >= it.cur; }

        reference operator*() {
            if (cur != nullptr)
                return *cur;
            else
                throw std::runtime_error("Iterator refer to null");
        }

        pointer operator->() {
            if (cur != nullptr)
                return cur;
            else
                throw std::runtime_error("Iterator refer to null");
        }

        reference operator[](difference_type n) const {
            if (index + n >= ptr->size)
                throw std::out_of_range("Iterator out of working zone([])");
            return *(cur + n);
        }
    };

    Iterator begin() { return Iterator(data, 0, this); }

    Iterator end() { return Iterator(data + size, size, this); }

    friend Iterator;
};
