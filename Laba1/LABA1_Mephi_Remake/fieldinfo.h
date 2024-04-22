#ifndef LABA1_MEPHI_REMAKE_FIELDINFO_H
#define LABA1_MEPHI_REMAKE_FIELDINFO_H

#include <stdio.h>


typedef void *(*BinaryOperation)(void *a, void *b, void *result);

typedef void *(*UnaryOperation)(void *elem);

typedef void *(*InputFromFile)(FILE *file, void *elem);


typedef struct {
    BinaryOperation add;
    BinaryOperation multiply;
    UnaryOperation zero;
    UnaryOperation input;
    UnaryOperation print;
    InputFromFile inputFromFile;
    int elemSize;
}FieldInfo;


#endif //LABA1_MEPHI_REMAKE_FIELDINFO_H
