#include <stdio.h>
#include "fieldinfo.h"
#include "vector.h"
#include "double.h"
#include "complex.h"
#include "integer.h"
#include "test.h"


void inputVectorFromFile(Vector *vector, FILE *file) {
    for (int i = 0; i < vector->size; i++) {
        vector->base->inputFromFile(file, vector->data + i * vector->base->elemSize);
    }
}

void runTest(const char* filename, FieldInfo* fieldInfo) {
    int size;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }
    fscanf(file, "%d", &size);

    Vector *vector1 = newVector(size, fieldInfo);
    Vector *vector2 = newVector(size, fieldInfo);
    Vector *result = newVector(size, fieldInfo);

    inputVectorFromFile(vector1, file);
    inputVectorFromFile(vector2, file);

    printf("Vector 1: ");
    printVector(vector1);
    printf("Vector 2: ");
    printVector(vector2);

    addVectors(vector1, vector2, result);
    printf("Result of addition:\n");
    printVector(result);

    scalarMultiply(vector1, vector2);

    destroyVector(vector1);
    destroyVector(vector2);
    destroyVector(result);

    fclose(file);
}

void runIntegerTest(const char* filename) {
    runTest(filename, getIntImplementation());
}

void runDoubleTest(const char* filename) {
    runTest(filename, getDoubleImplementation());
}

void runComplexTest(const char* filename) {
    runTest(filename, getComplexImplementation());
}
