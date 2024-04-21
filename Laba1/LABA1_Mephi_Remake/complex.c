#include "complex.h"
#include <stdio.h>
#include <malloc.h>

typedef struct {
    int real;
    int imaginary;
} Complex;

void *complexAddition(void *a, void *b, void *result) {
    Complex *res = (Complex *)result;
    res->real = ((Complex *)a)->real + ((Complex *)b)->real;
    res->imaginary = ((Complex *)a)->imaginary + ((Complex *)b)->imaginary;
    return (void *)res;
}

void *complexMultiplication(void *a, void *b, void *result) {
    Complex *c1 = (Complex *)a;
    Complex *c2 = (Complex *)b;
    Complex *res = (Complex *)result;
    res->real = (c1->real * c2->real) - (c1->imaginary * c2->imaginary);
    res->imaginary = (c1->real * c2->imaginary) + (c1->imaginary * c2->real);
    return (void *)res;
}

void complexPutZero(void *elem) {
    Complex *c = (Complex *)elem;
    c->real = 0;
    c->imaginary = 0;
}

void *complexInputElement(void *elem) {
    printf("Enter real part of the complex number: ");
    int real;
    scanf("%d", &real);
    printf("Enter imaginary part of the complex number: ");
    int imaginary;
    scanf("%d", &imaginary);
    Complex *c = (Complex *)elem;
    c->real = real;
    c->imaginary = imaginary;
    return elem;
}

void *complexPrintElement(void *a) {
    Complex *c = (Complex *)a;
    printf("%d + %di", c->real, c->imaginary);
    return NULL;
}

void *complexInputFromFile(FILE *file, void *elem) {
    Complex *c = (Complex *)elem;
    fscanf(file, "%d %d", &(c->real), &(c->imaginary));
    return elem;
}

FieldInfo *getComplexImplementation() {
    FieldInfo *complexInfo = malloc(sizeof(FieldInfo));
    complexInfo->add = &complexAddition;
    complexInfo->multiply = &complexMultiplication;
    complexInfo->zero = &complexPutZero;
    complexInfo->input = &complexInputElement;
    complexInfo->print = &complexPrintElement;
    complexInfo->inputFromFile = &complexInputFromFile;
    complexInfo->elemSize = sizeof(Complex);
    return complexInfo;
}
