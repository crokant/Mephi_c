#pragma once

#include "../Laba2/LABA2_Mephi/MutableArraySequence.h"
#include <complex>
#include <stdexcept>
#include <cmath>

using namespace std;

template<typename T>
class Vector {
private:
    MutableArraySequence<T> coordinates;

    void append(const T &item) {
        coordinates.append(item);
    }

public:
    Vector() : coordinates() {}

    Vector(T *items, int length) : coordinates(items, length) {}

    const T &get(int index) const {
        return coordinates.get(index);
    }

    int getSize() const {
        return coordinates.getLength();
    }

    Vector<T> *add(const Vector<T> &other) const {
        if (coordinates.getLength() != other.getSize()) {
            throw invalid_argument("VectorsCanNotBeAdd");
        }
        auto *result = new Vector<T>();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result->append(coordinates.get(i) + other.coordinates.get(i));
        }
        return result;
    }

    T dotProduct(const Vector<T> &other) const {
        if (coordinates.getLength() != other.getSize()) {
            throw invalid_argument("VectorsCanNotBeMultiply");
        }
        T result = T();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result += coordinates.get(i) * other.coordinates.get(i);
        }
        return result;
    }

    Vector<T> *multiplyByScalar(const T &scalar) const {
        auto *result = new Vector<T>();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result->append(coordinates.get(i) * scalar);
        }
        return result;
    }

    T normCalculate() const {
        T norm = T();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            norm += pow(coordinates.get(i), 2);
        }
        return sqrt(norm);
    }
};
