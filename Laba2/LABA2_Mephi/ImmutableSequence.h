#pragma once


template<class T>
class ImmutableSequence {
public:
    virtual ~ImmutableSequence() = default;

    virtual const T &get(int index) const = 0;

    virtual const T &getFirst() const = 0;

    virtual const T &getLast() const = 0;

    virtual ImmutableSequence<T> *getSubSequence(int startIndex, int endIndex) = 0;

    virtual int getLength() const = 0;

    virtual ImmutableSequence<T> *append(const T item) const = 0;

    virtual ImmutableSequence<T> *prepend(const T item) const = 0;

    virtual ImmutableSequence<T> *insertAt(int index, const T item) const = 0;

    virtual ImmutableSequence<T> *concat(ImmutableSequence<T> *sequence) const = 0;
};
