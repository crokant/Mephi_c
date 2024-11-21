#pragma once

#include "Student.h"
#include "../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"

int generateRandomNumber(int min, int max);

void generateRandomArray(int *arr, int size, int min, int max);

double generateRandomDouble(int min, int max, int accuracy);

Student generateStudent();

void generateStudentArray(Student *arr, int size);