#include "Vector.h"
#include "SquareMatrix.h"
#include "VisualConsoleDesign.h"
#include "VectorInteraction.h"
#include "MatrixInteraction.h"
#include <iostream>
#include <complex>

#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;


int dataTypeMenu() {
    int choice;
    cout << MAGENTA << "Choose data type:"
                       "\n>>1 (for int)"
                       "\n>>2 (for double)"
                       "\n>>3 (for complex)"
         << RESET << "\n<<";
    consoleInput(choice);
    return choice;
}

template<typename T>
void vectorMainMenu(Vector<T> &vector) {
    int choice;
    do {
        cout << CYAN << "Choose an operation:\n"
                        ">>1 Add\n"
                        ">>2 Dot Product\n"
                        ">>3 Multiply by Scalar\n"
                        ">>4 Calculate Norm\n"
                        ">>5 Print Vector\n"
                        ">>6 Exit"
             << RESET << "\n<<";
        consoleInput(choice);
        switch (choice) {
            case 1:
                addition(vector);
                break;
            case 2:
                scalarMultiplication(vector);
                break;
            case 3:
                multiplicationByScalar(vector);
                break;
            case 4:
                cout << "Norm: " << vector.normCalculate() << endl;
                break;
            case 5:
                vector.print();
                break;
            case 6:
                cout << YELLOW << "Exiting vector operations" << RESET << "\n";
                break;
            default:
                cout << "Invalid choice";
        }
    } while (choice != 6);
}

template<typename T>
void matrixMainMenu(SquareMatrix<T> &matrix) {
    int choice;
    do {
        cout << MAGENTA << "Choose an operation:\n"
                           ">>1 Add\n"
                           ">>2 Multiply by Scalar\n"
                           ">>3 Calculate Norm\n"
                           ">>4 Swap Rows\n"
                           ">>5 Swap Columns\n"
                           ">>6 Multiply Row by Scalar\n"
                           ">>7 Multiply Column by Scalar\n"
                           ">>8 Add Rows\n"
                           ">>9 Add Columns\n"
                           ">>10 Print Matrix\n"
                           ">>11 Exit"
             << RESET << "\n<<";
        consoleInput(choice);
        switch (choice) {
            case 1:
                addition(matrix);
                break;
            case 2:
                multiplicationByScalar(matrix);
                break;
            case 3:
                cout << "Norm: " << matrix.normCalculate() << endl;
                break;
            case 4:
                rowsSwap(matrix);
                break;
            case 5:
                columnsSwap(matrix);
                break;
            case 6:
                multiplyRow(matrix);
                break;
            case 7:
                multiplyColumn(matrix);
                break;
            case 8:
                rowsAddition(matrix);
                break;
            case 9:
                columnsAddition(matrix);
                break;
            case 10:
                matrix.print();
                break;
            case 11:
                cout << YELLOW << "Exiting matrix operations" << RESET << "\n";
                break;
            default:
                cout << "Invalid choice. Please choose again\n";
        }
    } while (choice != 11);
}

void vectorDataType() {
    int choice = dataTypeMenu();
    if (choice == 1) {
        Vector<int> intVector = createVector<int>();
        vectorMainMenu(intVector);
    } else if (choice == 2) {
        auto doubleVector = createVector<double>();
        vectorMainMenu(doubleVector);
    } else if (choice == 3) {
        auto complexVector = createVector<complex<double>>();
        vectorMainMenu(complexVector);
    } else {
        cout << "InvalidType" << endl;
    }
}

void matrixDataType() {
    int choice = dataTypeMenu();
    if (choice == 1) {
        auto intMatrix = createMatrix<int>();
        matrixMainMenu(intMatrix);
    } else if (choice == 2) {
        auto doubleMatrix = createMatrix<double>();
        matrixMainMenu(doubleMatrix);
    } else if (choice == 3) {
        auto complexMatrix = createMatrix<complex<double>>();
        matrixMainMenu(complexMatrix);
    } else {
        cout << "InvalidType" << endl;
    }
}

void startMenu() {
    int choice;
    cout << "\nif all tests are passed, you can continue\n";
    do {
        cout << MAGENTA << "\nChoose an option:\n"
                           ">>1 Vector\n"
                           ">>2 SquareMatrix\n"
                           ">>3 Exit"
             << RESET << "\n<<";
        consoleInput(choice);
        switch (choice) {
            case 1:
                vectorDataType();
                break;
            case 2:
                matrixDataType();
                break;
            case 3:
                cout << YELLOW << "Exiting menu" << RESET << "\n";
                break;
            default:
                cout << "Invalid choice. Please choose again\n";
        }
    } while (choice != 3);
}
