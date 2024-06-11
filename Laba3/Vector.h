#pragma once

#include "../Laba2/LABA2_Mephi/MutableArraySequence.h"
#include <complex>
#include <iostream>
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

    T &get(int index) {
        return coordinates.get(index);
    }

    int getSize() const {
        return coordinates.getLength();
    }

    Vector<T> *add(Vector<T> &other) {
        if (coordinates.getLength() != other.getSize()) {
            throw invalid_argument("VectorsCanNotBeAdd");
        }
        auto *result = new Vector<T>();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result->append(coordinates.get(i) + other.coordinates.get(i));
        }
        return result;
    }

    T dotProduct(Vector<T> &other) {
        if (coordinates.getLength() != other.getSize()) {
            throw invalid_argument("VectorsCanNotBeMultiply");
        }
        T result = T();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result += coordinates.get(i) * other.coordinates.get(i);
        }
        return result;
    }

    Vector<T> *multiplyByScalar(const T &scalar) {
        auto *result = new Vector<T>();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            result->append(coordinates.get(i) * scalar);
        }
        return result;
    }

    T normCalculate() {
        T sum = T();
        for (int i = 0; i < coordinates.getLength(); ++i) {
            sum += coordinates.get(i) * coordinates.get(i);
        }
        return sqrt(sum);
    }

    void print() {
        const char *prefix = "(";
        for (int i = 0; i < coordinates.getLength(); ++i) {
            cout << prefix << coordinates.get(i);
            prefix = "; ";
        }
        cout << ")" << endl;
    }
};
