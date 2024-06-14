#pragma once

#include "SquareMatrix.h"
#include "../Laba2/LABA2_Mephi/ConsoleInput.h"
#include <iostream>
#include <iomanip>

#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;

template<typename T>
void print(SquareMatrix<T> &matrix) {
    for (int i = 0; i < matrix.getSize(); ++i) {
        cout << "+";
        for (int j = 0; j < matrix.getSize(); ++j) {
            cout << "-------+";
        }
        cout << endl << "| ";
        for (int j = 0; j < matrix.getSize(); ++j) {
            cout << setw(5) << matrix.get(i, j) << " | ";
        }
        cout << endl;
    }
    cout << "+";
    for (int j = 0; j < matrix.getSize(); ++j) {
        cout << "-------+";
    }
    cout << endl;
}

template<typename T>
SquareMatrix<T> createMatrix(int size = -1) {
    if (size == -1) {
        cout << "Enter size of matrix (NxN): ";
        consoleInput(size);
    }
    T *elements = new T[size * size];
    cout << "Enter elements of the matrix: ";
    for (int i = 0; i < size * size; ++i) {
        consoleInput(elements[i]);
    }
    SquareMatrix<T> matrix(elements, size);
    delete[] elements;
    return matrix;
}

template<typename T>
void addition(SquareMatrix<T> &matrix) {
    cout << YELLOW << "Enter second matrix. Matrices have to be the same size" << RESET << endl;
    auto other = createMatrix<T>(matrix.getSize());
    print(*matrix.add(other));
}

template<typename T>
void multiplicationByScalar(SquareMatrix<T> &matrix) {
    T scalar;
    cout << "Enter scalar: ";
    consoleInput(scalar);
    print(*matrix.multiplyByScalar(scalar));
}

template<typename T>
void rowsSwap(SquareMatrix<T> &matrix) {
    int row1, row2;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter two rows to swap: ";
    consoleInput(row1);
    consoleInput(row2);
    matrix.swapRows(row1, row2);
}

template<typename T>
void columnsSwap(SquareMatrix<T> &matrix) {
    int column1, column2;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter two columns to swap: ";
    consoleInput(column1);
    consoleInput(column2);
    matrix.swapColumns(column1, column2);
}

template<typename T>
void multiplyRow(SquareMatrix<T> &matrix) {
    int row;
    T scalar;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter row to multiply: ";
    consoleInput(row);
    cout << "Enter scalar: ";
    consoleInput(scalar);
    matrix.multiplyRowByScalar(row, scalar);
}

template<typename T>
void multiplyColumn(SquareMatrix<T> &matrix) {
    int column;
    T scalar;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter column to multiply: ";
    consoleInput(column);
    cout << "Enter scalar: ";
    consoleInput(scalar);
    matrix.multiplyColumnByScalar(column, scalar);
}

template<typename T>
void rowsAddition(SquareMatrix<T> &matrix) {
    int row1, row2;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter two raws(1+=2): ";
    consoleInput(row1);
    consoleInput(row2);
    matrix.addRows(row1, row2);
}

template<typename T>
void columnsAddition(SquareMatrix<T> &matrix) {
    int column1, column2;
    cout << YELLOW << "WARNING: numbers of columns and rows of matrix start from ZERO" << RESET << "\n";
    cout << "Enter two columns(1+=2): ";
    consoleInput(column1);
    consoleInput(column2);
    matrix.addColumns(column1, column2);
}
