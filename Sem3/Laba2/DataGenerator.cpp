#include "DataGenerator.h"
#include <random>
#include "SortUi.h"


int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void generateRandomArray(int *arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = generateRandomNumber(min, max);
    }
}

