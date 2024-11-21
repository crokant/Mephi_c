#include <cassert>
#include <iostream>
#include <chrono>
#include "tests.h"
#include "sorting/ISorter.h"

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET  "\033[0m"

template<typename T>
bool isSorted(const DynamicArray<T> &dynamic, std::function<bool(const T &, const T &)> comp) {
    for (int i = 1; i < dynamic.getSize() - 1; ++i) {
        if (comp(dynamic[i], dynamic[i - 1])) {
            return false;
        }
    }
    return true;
}

void runPerformanceTest(ISorter<int> &sorter, const std::string &sorterName, int dataSize) {
    int arr[dataSize];
    std::function<bool(const int &, const int &)> comp = [](const int &a, const int &b) { return a < b; };
    generateRandomArray(arr, dataSize, INT_MIN / 100, INT_MAX / 100);
    DynamicArray<int> dynamic(arr, dataSize);
    auto start = std::chrono::steady_clock::now();

    sorter.sort(dynamic.begin(), dynamic.end(), comp);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(25) << std::left << sorterName
              << std::setw(10) << std::right << dataSize
              << std::setw(20) << std::right << duration.count() << " ms" << std::endl;
}

void sortersPerformanceTest(ISorter<Student> &sorter, const std::string &sorterName) {
    std::cout << RED << sorterName << "Not realized" << RESET << std::endl;
}

void sortersPerformanceTest(ISorter<int> &sorter, const std::string &sorterName) {
    std::cout << std::string(60, '-') << std::endl;
    runPerformanceTest(sorter, sorterName, 100);
    runPerformanceTest(sorter, sorterName, 1000);
    runPerformanceTest(sorter, sorterName, 10000);
}

void supSortersTestStudents(ISorter<Student> &sorter, const std::string &sorterName,
                            std::function<bool(const Student &, const Student &)> &comp, int dataSize) {
    Student arr[dataSize];
    generateStudentArray(arr, dataSize);
    DynamicArray<Student> dynamic(arr, dataSize);
    sorter.sort(dynamic.begin(), dynamic.end(), comp);

    if (!isSorted(dynamic, comp)) {
        std::cout << RED << sorterName << " test failed" << RESET << std::endl;
    } else {
        std::cout << GREEN << sorterName << " test passed" << RESET << std::endl;
    }
}

void sortersFunctionalityTest(ISorter<Student> &sorter, const std::string &sorterName, int dataSize) {
    std::function<bool(const Student &, const Student &)> compAge = Student::compareByAge;
    std::function<bool(const Student &, const Student &)> compScore = Student::compareByAverageScore;
    std::function<bool(const Student &, const Student &)> compCourse = Student::compareByCourse;
    supSortersTestStudents(sorter, sorterName + " - Students by age", compAge, dataSize);
    supSortersTestStudents(sorter, sorterName + " - Students by average score", compScore, dataSize);
    supSortersTestStudents(sorter, sorterName + " - Students by course", compCourse, dataSize);
}

void sortersFunctionalityTest(ISorter<int> &sorter, const std::string &sorterName, int dataSize) {
    int arr[dataSize];
    std::function<bool(const int &, const int &)> comp = [](const int &a, const int &b) { return a < b; };
    generateRandomArray(arr, dataSize, INT_MIN / 100, INT_MAX / 100);
    DynamicArray<int> dynamic(arr, dataSize);
    sorter.sort(dynamic.begin(), dynamic.end(), comp);

    if (!isSorted(dynamic, comp)) {
        std::cout << RED << sorterName << " - int test failed" << RESET << std::endl;
    } else {
        std::cout << GREEN << sorterName << " - int test passed" << RESET << std::endl;

    }
}

