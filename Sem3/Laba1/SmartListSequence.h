#pragma once

#include "UniquePtr.h"
#include "SmartList.h"
#include "Sequence.h"

template<class T>
class SmartListSequence : public Sequence<T> {
private:
    UniquePtr<SmartList<T>> base;

public:
    SmartListSequence() : base{new SmartList<T>()} {}

    SmartListSequence(T *items, int size) : base{new SmartList<T>(items, size)} {}

    explicit SmartListSequence(const SmartList<T> &list) : base{new SmartList<T>(list)} {}

    SmartListSequence(SmartListSequence &&other) noexcept: base{std::move(other.base)} {}

    SmartListSequence &operator=(const SmartListSequence &other) {
        if (this != &other) {
            base.reset(new SmartList<T>(*other.base));
        }
        return *this;
    }

    const T &getFirst() const override {
        return base->getFirst();
    }

    const T &getLast() const override {
        return base->getLast();
    }

    const T &get(int index) const override {
        return base->getByIndex(index);
    }

    SharedPtr<Sequence<T>> getSubSequence(int startIndex, int endIndex) override {
        SmartList<T> subList = base->getSubList(startIndex, endIndex);
        return SharedPtr<Sequence<T>>(new SmartListSequence<T>(subList));
    }

    [[nodiscard]] int getLength() const override {
        return base->getLength();
    }

    void append(const T &item) override {
        base->append(item);
    }

    void prepend(const T &item) override {
        base->prepend(item);
    }

    void insertAt(int index, const T &item) override {
        base->insertAt(index, item);
    }

    void concat(Sequence<T> &sequence) override {
        for (int i = 0; i < sequence.getLength(); ++i) {
            base->append(sequence.get(i));
        }
    }
};
