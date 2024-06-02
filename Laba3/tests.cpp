#include "tests.h"
#include "Vector.h"
#include "SquareMatrix.h"
#include <iostream>
#include <cassert>

using namespace std;

#define GREEN "\033[32m"
#define RESET "\033[0m"

void testVectorAddition() {
    int intArray[] = {1, 2, 3};
    Vector<int> intVec(intArray, 3);
    Vector<int> intVec2(intArray, 3);
    Vector<int> *intVecSum = intVec.add(intVec2);

    assert(intVecSum->get(0) == 2);
    assert(intVecSum->get(1) == 4);
    assert(intVecSum->get(2) == 6);

    delete intVecSum;
    cout << GREEN << "testVectorAddition passed" << RESET << endl;
}

void testVectorDotProduct() {
    int intArray[] = {1, 2, 3};
    Vector<int> intVec(intArray, 3);
    Vector<int> intVec2(intArray, 3);
    int intDotProduct = intVec.dotProduct(intVec2);

    assert(intDotProduct == 14);
    cout << GREEN << "testVectorDotProduct passed" << RESET << endl;
}

void testVectorMultiplicationByScalar() {
    int intArray[] = {1, 2, 3};
    Vector<int> intVec(intArray, 3);
    Vector<int> *intVecScaled = intVec.multiplyByScalar(3);

    assert(intVecScaled->get(0) == 3);
    assert(intVecScaled->get(1) == 6);
    assert(intVecScaled->get(2) == 9);

    delete intVecScaled;
    cout << GREEN << "testVectorScalarMultiplication passed" << RESET << endl;
}

void testVectorNorm() {
    double array[] = {1, 2, 3};
    Vector<double> vec(array, 3);
    auto norm = vec.normCalculate();
    assert(abs(norm - 3.74166) <= 1e-5);
    cout << GREEN << "testVectorNorm passed" << RESET << endl;
}

void testMatrixAddition() {
    int intArray[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    SquareMatrix<int> intMatrix(intArray, 3);
    SquareMatrix<int> intMatrix2(intArray, 3);
    SquareMatrix<int> *intMatrixSum = intMatrix.add(intMatrix2);

    assert(intMatrixSum->get(0, 0) == 2);
    assert(intMatrixSum->get(0, 1) == 4);
    assert(intMatrixSum->get(0, 2) == 6);
    assert(intMatrixSum->get(1, 0) == 8);
    assert(intMatrixSum->get(1, 1) == 10);
    assert(intMatrixSum->get(1, 2) == 12);
    assert(intMatrixSum->get(2, 0) == 14);
    assert(intMatrixSum->get(2, 1) == 16);
    assert(intMatrixSum->get(2, 2) == 18);

    delete intMatrixSum;
    cout << GREEN << "testMatrixAddition passed" << RESET << endl;
}

void testMatrixScalarMultiplication() {
    int intArray[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    SquareMatrix<int> intMatrix(intArray, 3);
    SquareMatrix<int> *intMatrixScaled = intMatrix.multiplyByScalar(3);

    assert(intMatrixScaled->get(0, 0) == 3);
    assert(intMatrixScaled->get(0, 1) == 6);
    assert(intMatrixScaled->get(0, 2) == 9);
    assert(intMatrixScaled->get(1, 0) == 12);
    assert(intMatrixScaled->get(1, 1) == 15);
    assert(intMatrixScaled->get(1, 2) == 18);
    assert(intMatrixScaled->get(2, 0) == 21);
    assert(intMatrixScaled->get(2, 1) == 24);
    assert(intMatrixScaled->get(2, 2) == 27);

    delete intMatrixScaled;
    cout << GREEN << "testMatrixScalarMultiplication passed" << RESET << endl;
}

void testMatrixNorm() {
    double array[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    SquareMatrix<double> matrix(array, 3);
    auto matrixNorm = matrix.normCalculate();

    assert(std::abs(matrixNorm - 16.8819) < 1e-4);
    cout << GREEN << "testMatrixNorm passed" << RESET << endl;
}

void testMatrixRowOperations() {
    int intArray[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    SquareMatrix<int> intMatrix(intArray, 3);
    intMatrix.swapRows(0, 1);
    assert(intMatrix.get(0, 0) == 4);
    assert(intMatrix.get(0, 1) == 5);
    assert(intMatrix.get(0, 2) == 6);
    assert(intMatrix.get(1, 0) == 1);
    assert(intMatrix.get(1, 1) == 2);
    assert(intMatrix.get(1, 2) == 3);

    intMatrix.multiplyRowByScalar(1, 2);
    assert(intMatrix.get(1, 0) == 2);
    assert(intMatrix.get(1, 1) == 4);
    assert(intMatrix.get(1, 2) == 6);

    intMatrix.addRows(0, 1);
    assert(intMatrix.get(0, 0) == 6);
    assert(intMatrix.get(0, 1) == 9);
    assert(intMatrix.get(0, 2) == 12);

    cout << GREEN << "testMatrixRowOperations passed" << RESET << endl;
}

void testMatrixColumnOperations() {
    int intArray[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    SquareMatrix<int> intMatrix(intArray, 3);
    intMatrix.swapColumns(0, 1);
    assert(intMatrix.get(0, 0) == 2);
    assert(intMatrix.get(0, 1) == 1);
    assert(intMatrix.get(1, 0) == 5);
    assert(intMatrix.get(1, 1) == 4);
    assert(intMatrix.get(2, 0) == 8);
    assert(intMatrix.get(2, 1) == 7);

    intMatrix.multiplyColumnByScalar(1, 2);
    assert(intMatrix.get(0, 1) == 2);
    assert(intMatrix.get(1, 1) == 8);
    assert(intMatrix.get(2, 1) == 14);

    intMatrix.addColumns(0, 1);
    assert(intMatrix.get(0, 0) == 4);
    assert(intMatrix.get(1, 0) == 13);
    assert(intMatrix.get(2, 0) == 22);

    cout << GREEN << "testMatrixColumnOperations passed" << RESET << endl;
}

void runVectorTests() {
    testVectorAddition();
    testVectorDotProduct();
    testVectorMultiplicationByScalar();
    testVectorNorm();
}

void runMatrixTests() {
    testMatrixAddition();
    testMatrixScalarMultiplication();
    testMatrixNorm();
    testMatrixRowOperations();
    testMatrixColumnOperations();
}
