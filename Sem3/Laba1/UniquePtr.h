#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class UniquePtr {
private:
    T *ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *ptr) : ptr(ptr) {}

    UniquePtr(UniquePtr<T> &&other) noexcept: ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr(const UniquePtr<T> &other) = delete;

    UniquePtr<T> &operator=(UniquePtr<T> &&other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UniquePtr<T> &operator=(const UniquePtr<T> &other) = delete;

    ~UniquePtr() {
        delete ptr;
    }

    T *get() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null UniquePtr");
        }
        return ptr;
    }

    const T &operator*() const {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null UniquePtr");
        }
        return *ptr;
    }

    T &operator*() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null UniquePtr");
        }
        return *ptr;
    }

    const T *operator->() const {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null UniquePtr");
        }
        return ptr;
    }

    T *operator->() {
        if (!ptr) {
            throw std::runtime_error("Attempted to access null UniquePtr");
        }
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    T *release() {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T *newPtr = nullptr) {
        delete ptr;
        ptr = newPtr;
    }
};
