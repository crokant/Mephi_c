#pragma once

#include "../Laba2/LABA2_Mephi/MutableArraySequence.h"
#include <complex>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>


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

    T &get(int row, int col) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return data.get(row * size + col);
    }

    SquareMatrix<T> *add(SquareMatrix<T> &other) {
        if (size != other.getSize()) {
            throw std::invalid_argument("MatricesCanNotBeAdd");
        }
        auto *result = new SquareMatrix<T>(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result->get(i, j) = this->get(i, j) + other.get(i, j);
            }
        }
        return result;
    }

    SquareMatrix<T> *multiplyByScalar(const T &scalar) {
        auto *result = new SquareMatrix<T>(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result->get(i, j) = this->get(i, j) * scalar;
            }
        }
        return result;
    }

    T normCalculate() {
        double sum = 0.0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                sum += std::abs(this->get(i, j)) * std::abs(this->get(i, j));
            }
        }
        return std::sqrt(sum);
    }

    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            std::swap(get(row1, col), get(row2, col));
        }
    }

    void swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            std::swap(get(row, col1), get(row, col2));
        }
    }

    void multiplyRowByScalar(int row, const T &scalar) {
        if (row < 0 || row >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            get(row, col) *= scalar;
        }
    }

    void multiplyColumnByScalar(int col, const T &scalar) {
        if (col < 0 || col >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            get(row, col) *= scalar;
        }
    }

    void addRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int col = 0; col < size; ++col) {
            get(row1, col) += get(row2, col);
        }
    }

    void addColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        for (int row = 0; row < size; ++row) {
            get(row, col1) += get(row, col2);
        }
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << "+";
            for (int j = 0; j < size; ++j) {
                std::cout << "-------+";
            }
            std::cout << std::endl << "| ";
            for (int j = 0; j < size; ++j) {
                std::cout << std::setw(5) << get(i, j) << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << "+";
        for (int j = 0; j < size; ++j) {
            std::cout << "-------+";
        }
        std::cout << std::endl;
    }
};


