#pragma once

#include "UniquePtr.h"
#include "SmartList.h"

template<class T>
class SmartListSequence {
private:
    UniquePtr<SmartList<T>> base;

public:
    SmartListSequence() : base{new SmartList<T>()} {}

    SmartListSequence(T *items, int size) : base{new SmartList<T>(items, size)} {}

    explicit SmartListSequence(const SmartList<T> list) : base{new SmartList<T>(list)} {}

    const T &getFirst() const {
        return base->getFirst();
    }

    const T &getLast() const {
        return base->getLast();
    }

    const T &get(int index) const {
        return base->getByIndex(index);
    }

    SmartListSequence<T> *getSubSequence(int startIndex, int endIndex) {
        return new SmartListSequence<T>(*base->getSubList(startIndex, endIndex));
    }

    [[nodiscard]] int getLength() const {
        return base->getLength();
    }

    void append(const T item) {
        base->append(item);
    }

    void prepend(const T item) {
        base->prepend(item);
    }

    void insertAt(int index, const T item) {
        base->insertAt(index, item);
    }

    void concat(SmartListSequence<T> *sequence) {
        for (int i = 0; i < sequence->getLength(); ++i) {
            base->append(sequence->get(i));
        }
    }
};
