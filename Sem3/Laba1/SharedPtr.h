#pragma once

#include <cstddef>

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
private:
    class Counter {
    public:
        size_t count;

        Counter() : count(1) {}
    };

    T *ptr;
    Counter *counter;

    void release() {
        if (counter) {
            if (--counter->count == 0) {
                delete ptr;
                delete counter;
            }
        }
    }

public:
    SharedPtr() : ptr(nullptr), counter(nullptr) {}

    explicit SharedPtr(T *ptr) : ptr(ptr), counter(new Counter()) {}

    SharedPtr(const SharedPtr<T> &other) : ptr(other.ptr), counter(other.counter) {
        if (counter) {
            counter->count++;
        }
    }

    explicit SharedPtr(const WeakPtr<T> &other) : ptr(other.ptr), counter(other.counter) {
        if (counter) {
            counter->count++;
        }
    }

    SharedPtr(SharedPtr &&other) noexcept: ptr(other.ptr), counter(other.counter) {
        other.ptr = nullptr;
        other.counter = nullptr;
    }

    ~SharedPtr() {
        release();
    }

    SharedPtr<T> &operator=(const SharedPtr<T> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            counter = other.counter;
            if (counter) {
                counter->count++;
            }
        }
        return *this;
    }

    SharedPtr<T> &operator=(SharedPtr<T> &&other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            counter = other.counter;
            other.ptr = nullptr;
            other.counter = nullptr;
        }
        return *this;
    }

    T *get() { return ptr; }

    const T &operator*() const { return *ptr; }

    T &operator*() { return *ptr; }

    const T *operator->() const { return ptr; }

    T *operator->() { return ptr; }

    bool operator!() const {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    [[nodiscard]] size_t useCount() const {
        return counter ? counter->count : 0;
    }

    void swap(SharedPtr<T> &other) {
        T *temp_ptr = ptr;
        ptr = other.ptr;
        other.ptr = temp_ptr;
        Counter *temp_counter = counter;
        counter = other.counter;
        other.counter = temp_counter;
    }

    void reset() {
        release();
        ptr = nullptr;
        counter = nullptr;
    }

    friend class WeakPtr<T>;
};


