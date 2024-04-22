#include <stdio.h>
#include "fieldinfo.h"
#include "vector.h"
#include "double.h"
#include "complex.h"
#include "integer.h"
#include "test.h"

void operationChoose(const Vector* vectorA, const Vector* vectorB, Vector* result) {
    char operation;
    printf("Choose the operation\n'1' for sum two vectors, '2' for dot product of vectors\n");
    scanf(" %c", &operation);
    switch (operation - '0') {
        case '1' - '0':
            addVectors(vectorA, vectorB, result);
            printf("result of addition\n");
            printVector(result);
            break;
        case '2' - '0':
            printf("dot product\n");
            scalarMultiply(vectorA, vectorB);
            break;
        default:
            printf("the program does not support this operation");
            break;
    }
}

void inputVector(Vector* vector) {
    for (int i = 0; i < vector->size; i++) {
        vector->base->input(vector->data + i * vector->base->elemSize);
    }
}

void createVectors(FieldInfo* fieldInfo) {
    int size;
    printf("choose the size of your vectors, they must be the same size:\n");
    scanf("%d", &size);

    Vector *vector1 = newVector(size, fieldInfo);
    Vector *vector2 = newVector(size, fieldInfo);
    Vector *result = newVector(size, fieldInfo);

    printf("Enter elements for vector1:\n");
    inputVector(vector1);
    printf("Enter elements for vector2:\n");
    inputVector(vector2);

    printVector(vector1);
    printVector(vector2);

    operationChoose(vector1, vector2, result);

    destroyVector(vector1);
    destroyVector(vector2);
    destroyVector(result);
}


int main(void) {

    runIntegerTest("..//tests//testInt.txt");

    runComplexTest("..//tests//testComplex.txt");

    runDoubleTest("..//tests//testDouble.txt");

    char type;
    printf("I chose variant 1, which involves the implementation of an n-dimensional vector"
           " and its methods such as vector addition and scalar product\n");

    printf("choose vectors type\n'i' for integer, 'd' for real, 'c' for complex\n");
    scanf(" %c", &type);
    switch (type - '0') {
        case 'i' - '0':
            createVectors(getIntImplementation());
            break;
        case 'd' - '0':
            createVectors(getDoubleImplementation());
            break;
        case 'c' - '0':
            createVectors(getComplexImplementation());
            break;
        default:
            printf("the program does not support this\n");
            break;
    }
}