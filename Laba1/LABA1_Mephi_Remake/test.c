#include <stdio.h>
#include "fieldinfo.h"
#include "vector.h"
#include "double.h"
#include "complex.h"
#include "integer.h"
#include "test.h"

void runTest(const char* filename, FieldInfo* fieldInfo) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Failed to open file.\n");
        return;
    }

    int size;
    fscanf(file, "%d", &size);

    Vector *vector1 = newVector(size, fieldInfo);
    Vector *vector2 = newVector(size, fieldInfo);
    Vector *result = newVector(size, fieldInfo);

    for (int i = 0; i < size; ++i) {
        vector1->base->inputFromFile(file, vector1->data + i * vector1->base->elemSize);
    }

    for (int i = 0; i < size; ++i) {
        vector2->base->inputFromFile(file, vector2->data + i * vector2->base->elemSize);
    }

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
