#include <stdio.h>
#include <stdlib.h>
#include "fieldinfo.h"
#include "vector.h"
#include "double.h"
#include "complex.h"
#include "integer.h"
#include "test.h"

void runIntegerTest(const char* filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Failed to open file.\n");
        return;
    }

    FieldInfo *intInfo = getIntImplementation();
    int size;
    fscanf(file, "%d", &size);

    Vector *vector1 = newVector(size, intInfo);
    Vector *vector2 = newVector(size, intInfo);
    Vector *result = newVector(size, intInfo);

    for (int i = 0; i < size; ++i) {
        intInfo->inputFromFile(file, vector1->data + i * intInfo->elemSize);
    }

    for (int i = 0; i < size; ++i) {
        intInfo->inputFromFile(file, vector2->data + i * intInfo->elemSize);
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


