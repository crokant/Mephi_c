#pragma once

#include "Vector.h"
#include "../Laba2/LABA2_Mephi/ConsoleInput.h"
#include <iostream>

#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;

template<typename T>
void print(Vector<T> &vector) {
    const char *prefix = "(";
    for (int i = 0; i < vector.getSize(); ++i) {
        cout << prefix << vector.get(i);
        prefix = "; ";
    }
    cout << ")" << endl;
}

template<typename T>
Vector<T> createVector(int size = -1) {
    if (size == -1) {
        cout << "Enter size of vector: ";
        consoleInput(size);
    }
    T *items = new T[size];
    cout << "Enter elements of the vector: ";
    for (int i = 0; i < size; ++i) {
        consoleInput(items[i]);
    }
    Vector<T> vector(items, size);
    delete[] items;
    return vector;

}

template<typename T>
void addition(Vector<T> &vector) {
    cout << YELLOW << "Enter second vector. Vectors have to be the same size" << RESET << endl;
    auto other = createVector<T>(vector.getSize());
    print(*vector.add(other));
}

template<typename T>
void scalarMultiplication(Vector<T> &vector) {
    cout << YELLOW << "Enter second vector. Vectors have to be the same size" << RESET << endl;;
    auto other = createVector<T>(vector.getSize());
    cout << "Dot product: " << vector.dotProduct(other) << endl;
}

template<typename T>
void multiplicationByScalar(Vector<T> &vector) {
    T scalar;
    cout << "Enter scalar: ";
    consoleInput(scalar);
    print(*vector.multiplyByScalar(scalar));
}
