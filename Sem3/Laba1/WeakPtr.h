#pragma once

#include <stdexcept>
#include "SharedPtr.h"

template<typename T>
class WeakPtr {
private:
    T *ptr;
    typename SharedPtr<T>::Counter *counter;

    void release() {
        if (counter && --counter->weakCount == 0 && counter->sharedCount == 0) {
            delete counter;
        }
    }

public:
    WeakPtr() : ptr(nullptr), counter(nullptr) {}

    explicit WeakPtr(const SharedPtr<T> &sharedPtr) : ptr(sharedPtr.ptr), counter(sharedPtr.counter) {
        if (counter) {
            counter->weakCount++;
        }
    }

    WeakPtr(const WeakPtr<T> &other) : ptr(other.ptr), counter(other.counter) {
        if (counter) {
            counter->weakCount++;
        }
    }

    ~WeakPtr() {
        release();
    }

    WeakPtr<T> &operator=(const WeakPtr<T> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            counter = other.counter;
            if (counter) {
                counter->weakCount++;
            }
        }
        return *this;
    }

    WeakPtr<T> &operator=(const SharedPtr<T> &sharedPtr) {
        release();
        ptr = sharedPtr.ptr;
        counter = sharedPtr.counter;
        if (counter) {
            counter->weakCount++;
        }
        return *this;
    }

    const T &operator*() const {
        if (expired()) {
            throw std::runtime_error("Attempted to access expired WeakPtr");
        }
        return *ptr;
    }

    T &operator*() {
        if (expired()) {
            throw std::runtime_error("Attempted to access expired WeakPtr");
        }
        return *ptr;
    }

    const T *operator->() const {
        if (expired()) {
            throw std::runtime_error("Attempted to access expired WeakPtr");
        }
        return ptr;
    }

    T *operator->() {
        if (expired()) {
            throw std::runtime_error("Attempted to access expired WeakPtr");
        }
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    [[nodiscard]] bool expired() const {
        return !counter || counter->sharedCount == 0;
    }

    SharedPtr<T> lock() {
        return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }

    [[nodiscard]] size_t useCount() const {
        return counter ? counter->sharedCount : 0;
    }

    void reset() {
        release();
        ptr = nullptr;
        counter = nullptr;
    }

    friend SharedPtr<T>;
};
