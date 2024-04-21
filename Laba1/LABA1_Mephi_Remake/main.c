#include <stdio.h>
#include "fieldinfo.h"
#include "vector.h"
#include "double.h"
#include "complex.h"

int main(void) {

    FieldInfo* doubleInfo = getDoubleImplementation();
    Vector *vector1 = newVector(3, doubleInfo);
    Vector *vector2 = newVector(3, doubleInfo);
    Vector *result1 = newVector(3, doubleInfo);

    printf("Enter elements for vector 1:\n");
    for (int i = 0; i < 3; i++) {
        vector1->base->input(vector1->data + i * vector1->base->elemSize);
    }

    printf("Enter elements for vector 2:\n");
    for (int i = 0; i < 3; i++) {
        vector2->base->input(vector2->data + i * vector2->base->elemSize);
    }

    printf("Vector 1: ");
    printVector(vector1);
    printf("Vector 2: ");
    printVector(vector2);

    addVectors(vector1, vector2, result1);

    printf("Result of addition: ");
    printVector(result1);

    scalarMultiply(vector1, vector2);

    destroyVector(vector1);
    destroyVector(vector2);
    destroyVector(result1);

    FieldInfo* complexInfo = getComplexImplementation();
    Vector *vector3 = newVector(3, complexInfo);
    Vector *vector4 = newVector(3, complexInfo);
    Vector *result2 = newVector(3,complexInfo);
    printf("Enter elements for vector 3:\n");
    for (int i = 0; i < 3; i++) {
        vector3->base->input(vector3->data + i * vector3->base->elemSize);
    }

    printf("Enter elements for vector 4:\n");
    for (int i = 0; i < 3; i++) {
        vector4->base->input(vector4->data + i * vector4->base->elemSize);
    }

    printf("Vector 3: ");
    printVector(vector3);
    printf("Vector 4: ");
    printVector(vector4);

    addVectors(vector3, vector4, result2);
    printf("Result of addition: ");
    printVector(result2);
    scalarMultiply(vector3, vector4);
    destroyVector(vector3);
    destroyVector(vector4);
    destroyVector(result2);
    return 0;

}