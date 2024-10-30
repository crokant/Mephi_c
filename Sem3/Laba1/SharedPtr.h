#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
private:
    class Counter {
    public:
        size_t sharedCount;
        size_t weakCount;

        Counter() : sharedCount(1), weakCount(0) {}
    };

    T *ptr;
    Counter *counter;

    void release() {
        if (!counter) return;
        if (--counter->sharedCount > 0) return;
        delete ptr;
        if (counter->weakCount == 0) {
            delete counter;
        }
    }

public:
    SharedPtr() : ptr(nullptr), counter(nullptr) {}

    explicit SharedPtr(T *ptr) : ptr(ptr), counter(ptr ? new Counter() : nullptr) {}

    SharedPtr(const SharedPtr<T> &other) : ptr(other.ptr), counter(other.counter) {
        if (counter) {
            counter->sharedCount++;
        }
    }

    explicit SharedPtr(const WeakPtr<T> &other) : ptr(nullptr), counter(nullptr) {
        if (!other.expired()) {
            ptr = other.ptr;
            counter = other.counter;
            if (counter) {
                counter->sharedCount++;
            }
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
                counter->sharedCount++;
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

    T *get() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null SharedPtr");
        }
        return ptr;
    }

    const T &operator*() const {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null SharedPtr");
        }
        return *ptr;
    }

    T &operator*() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null SharedPtr");
        }
        return *ptr;
    }

    const T *operator->() const {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null SharedPtr");
        }
        return ptr;
    }

    T *operator->() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null SharedPtr");
        }
        return ptr;
    }

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
        return counter ? counter->sharedCount : 0;
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


