#pragma once


template<class T>
class ImmutableSequence {
public:
    virtual ~ImmutableSequence() = default;

    virtual T get(int index) const = 0;

    virtual T getFirst() const = 0;

    virtual T getLast() const = 0;

    virtual ImmutableSequence<T> *getSubSequence(int startIndex, int endIndex) = 0;

    virtual int getLength() const = 0;

    virtual ImmutableSequence<T> *append(const T item) const = 0;

    virtual ImmutableSequence<T> *prepend(const T item) const = 0;

    virtual ImmutableSequence<T> *insertAt(int index, const T item) const = 0;

    virtual ImmutableSequence<T> *concat(ImmutableSequence<T> *list) const = 0;
};
