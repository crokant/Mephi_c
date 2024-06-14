#pragma once

#include "../Laba2/LABA2_Mephi/MutableArraySequence.h"
#include <complex>
#include <stdexcept>
#include <cmath>

using namespace std;

template<typename T>
class SquareMatrix {
private:
    MutableArraySequence<T> data;
    int size;

public:
    SquareMatrix() : size(0) {}

    SquareMatrix(int size) : size(size), data(size * size) {}

    SquareMatrix(T *items, int size) : size(size), data(items, size * size) {}

    int getSize() const {
        return size;
    }

    void set(int row, int col, const T &value) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        data.set(row * size + col, value);
    }

    const T &get(int row, int col) const {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        return data.get(row * size + col);
    }

    SquareMatrix<T> *add(const SquareMatrix<T> &other) const {
        if (size != other.getSize()) {
            throw invalid_argument("MatricesCanNotBeAdd");
        }
        auto *result = new SquareMatrix<T>(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result->set(i, j, this->get(i, j) + other.get(i, j));
            }
        }
        return result;
    }

    SquareMatrix<T> *multiplyByScalar(const T &scalar) const {
        auto *result = new SquareMatrix<T>(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result->set(i, j, get(i, j) * scalar);
            }
        }
        return result;
    }

    T normCalculate() const {
        T sum = T();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                sum += pow(get(i, j), 2);
            }
        }
        return sqrt(sum);
    }

    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            T temp = get(row1, col);
            set(row1, col, get(row2, col));
            set(row2, col, temp);
        }
    }

    void swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            T temp = get(row, col1);
            set(row, col1, get(row, col2));
            set(row, col2, temp);
        }
    }

    void multiplyRowByScalar(int row, const T &scalar) {
        if (row < 0 || row >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            set(row, col, get(row, col) * scalar);
        }
    }

    void multiplyColumnByScalar(int col, const T &scalar) {
        if (col < 0 || col >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            set(row, col, get(row, col) * scalar);
        }
    }

    void addRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            set(row1, col, get(row1, col) + get(row2, col));
        }
    }

    void addColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            set(row, col1, get(row, col1) + get(row, col2));
        }
    }
};

