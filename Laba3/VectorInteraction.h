#pragma once

#include "Vector.h"
#include "../Laba2/LABA2_Mephi/ConsoleInput.h"
#include <iostream>

#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;

template<typename T>
Vector<T> createVector() {
    int size;
    cout << "Enter size of vector: ";
    consoleInput(size);
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
    cout << YELLOW << "Enter second vector. Please don`t try to make it different size" << RESET << endl;
    auto other = createVector<T>();
    vector.add(other)->print();
}

template<typename T>
void scalarMultiplication(Vector<T> &vector) {
    cout << YELLOW << "Enter second vector. Please don`t try to make it different size" << RESET << endl;;
    auto other = createVector<T>();
    cout << "Dot product: " << vector.dotProduct(other) << endl;
}

template<typename T>
void multiplicationByScalar(Vector<T> &vector) {
    T scalar;
    cout << "Enter scalar: ";
    consoleInput(scalar);
    vector.multiplyByScalar(scalar)->print();
}

