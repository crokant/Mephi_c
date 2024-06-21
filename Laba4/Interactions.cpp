#include <cstdlib>
#include "Interactions.h"
#include "../Laba2/LABA2_Mephi/ConsoleInput.h"
#include <chrono>
#include <ctime>

#define CYAN    "\033[36m"

using namespace std;
using namespace std::chrono;

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

steady_clock::time_point startTimer() {
    return steady_clock::now();
}

void endTimerAndPrint(const steady_clock::time_point &start, const string &operation) {
    auto end = steady_clock::now();
    auto diff = duration_cast<microseconds>(end - start);
    cout << CYAN << operation << " completed in " << diff.count() << " microseconds" << RESET << endl;
}

BinaryTree<int> createTree() {
    int num;
    cout << "Enter amount of elements: ";
    consoleInputOne(num);
    BinaryTree<int> tree;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < num; ++i) {
        int value = generateRandomNumber(1, 100000);
        tree.add(value);
    }
    return tree;
}

MinHeap<int> createHeap() {
    int num;
    cout << "Enter amount of elements: ";
    consoleInputOne(num);
    MinHeap<int> heap;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < num; ++i) {
        int value = generateRandomNumber(1, 100000);
        heap.insert(value);
    }
    return heap;
}

void findElementInTree(BinaryTree<int> &tree) {
    int value = 0;
    auto start = startTimer();
    bool found = tree.find(value);
    endTimerAndPrint(start, "Finding element in BinaryTree");
    cout << "Element " << (found ? "found" : "not found") << " in BinaryTree" << endl;
}

void findElementInHeap(MinHeap<int> &heap) {
    int value = generateRandomNumber(1, 100000);
    auto start = startTimer();
    bool found = heap.find(value);
    endTimerAndPrint(start, "Finding element in MinHeap");
    cout << "Element " << (found ? "found" : "not found") << " in MinHeap" << endl;
}

void removeElementFromTree(BinaryTree<int> &tree) {
    int value = generateRandomNumber(1, 100000);
    auto start = startTimer();
    try {
        tree.remove(value);
        endTimerAndPrint(start, "Removing element from BinaryTree");
    } catch (const invalid_argument &e) {
        cout << "Element not found in BinaryTree" << endl;
    }
}

void traverseTree(BinaryTree<int> &tree) {
    auto start = startTimer();
    auto vec = tree.getInOrderTraversal();
    endTimerAndPrint(start, "In order traversal of BinaryTree");
}

void traverseHeap(MinHeap<int> &heap) {
    auto start = startTimer();
    auto vec = heap.getInOrderTraversal();
    endTimerAndPrint(start, "In order traversal of BinaryHeap");
}



