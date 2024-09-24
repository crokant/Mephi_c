#include "integer.h"
#include <stdio.h>
#include <stdlib.h>


void *intAddition(void *a, void *b, void *result) {
    *(int *)result = *(int *)a + *(int *)b;
    return result;
}

void *intMultiplication(void *a, void *b, void *result) {
    *(int *)result = *(int *)a * *(int *)b;
    return result;
}

void *intPutZero(void *elem){
    *(int *)elem = 0;
}

void *intInputElement(void *elem) {
    printf("Enter an integer value: ");
    scanf("%d", (int*)elem);
    return elem;
}

void *intPrintElement(void *a) {
    printf("%d", *(int *)a);
    return NULL;
}

void *intInputFromFile(FILE *file, void *elem) {
    fscanf(file, "%d", (int *)elem);
    return elem;
}

FieldInfo *getIntImplementation() {
    static FieldInfo* intInfo = NULL;
    if (intInfo == NULL) {
        intInfo = malloc(sizeof(FieldInfo));
        intInfo->add = &intAddition;
        intInfo->multiply = &intMultiplication;
        intInfo->zero = &intPutZero;
        intInfo->input = &intInputElement;
        intInfo->print = &intPrintElement;
        intInfo->inputFromFile = &intInputFromFile;
        intInfo->elemSize = sizeof(int);
    }
    return intInfo;
}