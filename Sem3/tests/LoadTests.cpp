#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <iomanip>
#include "../Laba1/UniquePtr.h"
#include "../Laba1/SharedPtr.h"

template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template<typename PtrType>
void testPointer(size_t n, PtrType createPointer) {
    long long creationTime = measureTime([n, createPointer]() {
        for (size_t i = 0; i < n; i++) {
            auto ptr = createPointer(i);
        }
    });
    std::cout << std::setw(10) << "|" << std::setw(13) << creationTime;
}

void runPerformanceTests() {
    std::vector<size_t> testSizes = {100, 1000, 10000, 100000, 1000000};
    std::cout << "Pointers performance test\n";
    std::cout << "---------------------------------------------------------"
                 "---------------------------------------------------------\n";
    std::cout << "|     elements(N)      |   raw pointer(ms)    |  unique pointer(ms)  "
                 "|  shared pointer(ms)  |std::shared_ptr(ms) |\n";
    std::cout << "---------------------------------------------------------"
                 "---------------------------------------------------------\n";
    for (size_t n : testSizes) {
        std::cout << "|" << std::setw(13) << n;
        testPointer(n, [](size_t i) { int *ptr = new int(i); delete ptr; return ptr; });
        testPointer(n, [](size_t i) { return UniquePtr<int>(new int(i)); });
        testPointer(n, [](size_t i) { return SharedPtr<int>(new int(i)); });
        testPointer(n, [](size_t i) { return std::make_shared<int>(i); });
        std::cout << std::setw(9) << "|\n";
        std::cout << "---------------------------------------------------------"
                     "---------------------------------------------------------\n";
    }
}
