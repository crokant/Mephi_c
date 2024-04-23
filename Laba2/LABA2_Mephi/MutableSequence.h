#pragma once


template<class T>
class MutableSequence {
public:
    virtual ~MutableSequence() = default;

    virtual T get(int index) const = 0;

    virtual T getFirst() const = 0;

    virtual T getLast() const = 0;

    virtual MutableSequence<T> *getSubSequence(int startIndex, int endIndex) = 0;

    virtual int getLength() const = 0;

    virtual void append(const T item) = 0;

    virtual void prepend(const T item) = 0;

    virtual void insertAt(int index, const T item) = 0;

    virtual MutableSequence<T> *concat(MutableSequence<T> *list) = 0;
};
