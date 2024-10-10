#include "../UniquePtr.h"
#include "../SharedPtr.h"
#include "Graph.h"

#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <iomanip>

using namespace std;

template<typename Func>
long long measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

template<typename PtrType>
long long testPointer(size_t n, PtrType createPointer) {
    long long creationTime = measureTime([n, createPointer]() {
        for (size_t i = 0; i < n; i++) {
            auto ptr = createPointer(i);
        }
    });
    std::cout << std::setw(10) << "|" << std::setw(13) << creationTime;
    return creationTime;
}

void runPerformanceTests() {
    vector<size_t> testSizes = {100, 1000, 10000, 100000, 1000000};
    vector<long long> rawTimes;
    vector<long long> uniqueTimes;
    vector<long long> sharedTimes;
    vector<long long> stdSharedTimes;

    cout << "Pointers performance test\n";
    cout << "---------------------------------------------------------"
            "---------------------------------------------------------\n";
    cout << "|     elements(N)      |   raw pointer(ms)    |  unique pointer(ms)  "
            "|  shared pointer(ms)  | std::shared_ptr(ms) |\n";
    cout << "---------------------------------------------------------"
            "---------------------------------------------------------\n";

    for (size_t n : testSizes) {
        cout << "|" << setw(13) << n;
        rawTimes.push_back(testPointer(n, [](size_t i) { int *ptr = new int(i); delete ptr; return ptr; }));
        uniqueTimes.push_back(testPointer(n, [](size_t i) { return UniquePtr<int>(new int(i)); }));
        sharedTimes.push_back(testPointer(n, [](size_t i) { return SharedPtr<int>(new int(i)); }));
        stdSharedTimes.push_back(testPointer(n, [](size_t i) { return make_shared<int>(i); }));

        cout << setw(10) << "|\n";
        cout << "---------------------------------------------------------"
                "---------------------------------------------------------\n";
    }
    graph(testSizes, rawTimes, uniqueTimes, sharedTimes, stdSharedTimes);
}
