#ifndef LABA1_MEPHI_REMAKE_VECTOR_H
#define LABA1_MEPHI_REMAKE_VECTOR_H

#include "fieldinfo.h"
#include <stdio.h>

typedef struct {
    int size;
    void* data;
    FieldInfo* base;
}Vector;

Vector *newVector(int size, FieldInfo *impl);

void destroyVector(const Vector *target);

void printVector(const Vector *vector);

Vector *addVectors(const Vector *vectorA, const Vector *vectorB, Vector *result);

void scalarMultiply(const Vector *vectorA, const Vector *vectorB);


#endif //LABA1_MEPHI_REMAKE_VECTOR_H
