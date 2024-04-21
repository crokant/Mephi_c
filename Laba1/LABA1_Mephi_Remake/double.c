#include "double.h"
#include <stdio.h>
#include <malloc.h>


void *doubleAddition(void *a, void *b, void *result) {
    *(double *)result = *(double *)a + *(double *)b;
    return result;
}

void *doubleMultiplication(void *a, void *b, void *result) {
    *(double *)result = *(double *)a * *(double *)b;
    return result;
}

void doublePutZero(void *elem){
    *(double *)elem = 0;
}

void *doubleInputElement(void *elem) {
    printf("Enter a double value: ");
    scanf("%lf", (double*)elem);
    return elem;
}

void *doublePrintElement(void *a) {
    printf("%lf", *(double *)a);
    return NULL;
}

void *doubleInputFromFile(FILE *file, void *elem) {
    fscanf(file, "%lf", (double *)elem);
    return elem;
}

FieldInfo *getDoubleImplementation() {
    FieldInfo *doubleInfo = malloc(sizeof(FieldInfo));
    doubleInfo->add = &doubleAddition;
    doubleInfo->multiply = &doubleMultiplication;
    doubleInfo->zero = &doublePutZero;
    doubleInfo->input = &doubleInputElement;
    doubleInfo->print = &doublePrintElement;
    doubleInfo->inputFromFile = &doubleInputFromFile;
    doubleInfo->elemSize = sizeof(double);
    return doubleInfo;
}
