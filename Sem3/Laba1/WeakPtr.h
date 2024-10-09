#pragma once

#include "SharedPtr.h"

template<typename T>
class WeakPtr {
private:
    T *ptr;
    typename SharedPtr<T>::Counter *counter;

public:
    WeakPtr() : ptr(nullptr), counter(nullptr) {}

    explicit WeakPtr(const SharedPtr<T> &sharedPtr) : ptr(sharedPtr.ptr), counter(sharedPtr.counter) {}

    WeakPtr(const WeakPtr<T> &other) : ptr(other.ptr), counter(other.counter) {}

    WeakPtr<T> &operator=(const WeakPtr<T> &other) {
        if (this != &other) {
            ptr = other.ptr;
            counter = other.counter;
        }
        return *this;
    }

    WeakPtr<T> &operator=(const SharedPtr<T> &sharedPtr) {
        ptr = sharedPtr.ptr;
        counter = sharedPtr.counter;
        return *this;
    }

    T &operator*() const { return *ptr; }

    T &operator*() { return *ptr; }

    T *operator->() const { return ptr; }

    T *operator->() { return ptr; }

    bool gone() const {
        return !counter || counter->count == 0;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    SharedPtr<T> lock() const {
        return gone() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }

    size_t useCount() const {
        return counter ? counter->count : 0;
    }

    void reset() {
        ptr = nullptr;
        counter = nullptr;
    }

    friend SharedPtr<T>;
};
