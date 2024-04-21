#ifndef LABA1_MEPHI_REMAKE_FIELDINFO_H
#define LABA1_MEPHI_REMAKE_FIELDINFO_H

#include <stdio.h>

typedef struct FieldInfo FieldInfo;

typedef void *(*Addition)(void *a, void *b, void *result);

typedef void *(*Multiplication)(void *a, void *b, void *result);

typedef void (*PutZero)(void *elem);

typedef void *(*InputElement)(void *elem);

typedef void *(*PrintElement)(void *a);

typedef void *(*InputFromFile)(FILE *file, void *elem);



struct FieldInfo {
    Addition add;
    Multiplication multiply;
    PutZero zero;
    InputElement input;
    PrintElement print;
    InputFromFile inputFromFile;
    int elemSize;
};


#endif //LABA1_MEPHI_REMAKE_FIELDINFO_H
