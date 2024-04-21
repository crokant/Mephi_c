#include "vector.h"
#include <stdlib.h>


Vector* newVector(int size, FieldInfo* impl) {
    Vector* vector = malloc(sizeof(Vector));
    vector->size = size;
    vector->data = malloc(size * impl->elemSize);
    vector->base = impl;
    return vector;
}

void destroyVector(const Vector* vector) {
    if (vector != NULL) {
        free(vector->data);
        free(vector);
    }
}

void printVector(const Vector* vector) {
    if (vector == NULL) return;
    printf("(");
    for (int i = 0; i < vector->size; i++) {
        void* element = vector->data + i * vector->base->elemSize;
        vector->base->print(element);
        printf("; ");
    }
    printf(")\n");
}

Vector* addVectors(const Vector* vectorA, const Vector* vectorB, Vector* result) {
    if (vectorA == NULL || vectorB == NULL || result == NULL) return NULL;
    if (vectorA->size != vectorB->size || vectorA->size != result->size) return NULL;

    for (int i = 0; i < vectorA->size; i++) {
        void* elementA = vectorA->data + i * vectorA->base->elemSize;
        void* elementB = vectorB->data + i * vectorB->base->elemSize;
        void* resultElement = result->data + i * result->base->elemSize;
        result->base->add(elementA, elementB, resultElement);
    }

    return result;
}

void scalarMultiply(const Vector *vectorA, const Vector *vectorB) {
    if (vectorA == NULL || vectorB == NULL) return;
    if (vectorA->size != vectorB->size) return;

    void* result = malloc(vectorA->base->elemSize);
    vectorA->base->zero(result);
    for (int i = 0; i < vectorA->size; i++) {
        void* elementA = vectorA->data + i * vectorA->base->elemSize;
        void* elementB = vectorB->data + i * vectorB->base->elemSize;
        void* temp = malloc(vectorA->base->elemSize);
        vectorA->base->multiply(elementA, elementB, temp);
        result = vectorA->base->add(result, temp, result);
        free(temp);
    }
    printf("Dot product of vectors:\n");
    vectorA->base->print(result);
    printf("\n");
    free(result);
}




