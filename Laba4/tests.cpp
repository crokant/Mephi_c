#include "tests.h"
#include "BinaryTree.h"
#include "BinaryHeap.h"
#include <iostream>
#include <vector>
#include <cassert>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"

using namespace std;

void printTestResult(const string &testName) {
    cout << GREEN << testName << " passed" << RESET << endl;
}

void testCopyConstructor() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    BinaryTree<int> treeCopied(tree);
    assert(treeCopied.find(5));
    assert(treeCopied.find(3));
    assert(treeCopied.find(7));
    printTestResult("TestCopyConstructor");
}

void testAddAndFind() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    assert(tree.find(5));
    assert(tree.find(3));
    assert(tree.find(7));
    assert(tree.find(2));
    assert(tree.find(4));
    assert(tree.find(6));
    assert(tree.find(8));
    assert(!tree.find(10));
    printTestResult("TestAddAndFind");
}

void testRemove() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    tree.remove(3);
    assert(!tree.find(3));
    assert(tree.find(5));
    assert(tree.find(7));
    assert(tree.find(2));
    assert(tree.find(4));
    assert(tree.find(6));
    assert(tree.find(8));
    tree.remove(5);
    assert(!tree.find(5));
    assert(tree.find(7));
    assert(tree.find(2));
    assert(tree.find(4));
    assert(tree.find(6));
    assert(tree.find(8));
    printTestResult("TestRemove");
}

void testInOrderTraversal() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    vector<int> result = tree.getInOrderTraversal();
    vector<int> expected = {2, 3, 4, 5, 6, 7, 8};
    assert(result == expected);
    printTestResult("TestInOrderTraversal");
}

void testPreOrderTraversal() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    vector<int> result = tree.getPreOrderTraversal();
    vector<int> expected = {5, 3, 2, 4, 7, 6, 8};
    assert(result == expected);
    printTestResult("TestPreOrderTraversal");
}

void testPostOrderTraversal() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    vector<int> result = tree.getPostOrderTraversal();
    vector<int> expected = {2, 4, 3, 6, 8, 7, 5};
    assert(result == expected);
    printTestResult("TestPostOrderTraversal");
}

void testMerge() {
    int arr1[] = {5, 3, 7};
    int arr2[] = {2, 6, 8};
    BinaryTree<int> tree1(arr1, 3);
    BinaryTree<int> tree2(arr2, 3);
    BinaryTree<int> mergedTree = tree1.merge(tree2);
    assert(mergedTree.find(5));
    assert(mergedTree.find(3));
    assert(mergedTree.find(7));
    assert(mergedTree.find(2));
    assert(mergedTree.find(6));
    assert(mergedTree.find(8));
    vector<int> result = mergedTree.getInOrderTraversal();
    vector<int> expected = {2, 3, 5, 6, 7, 8};
    assert(result == expected);
    printTestResult("TestMerge");
}

void testExtractSubtree() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    BinaryTree<int> subtree = tree.extractSubtree(3);
    assert(subtree.find(3));
    assert(subtree.find(2));
    assert(subtree.find(4));
    assert(!subtree.find(5));
    assert(!subtree.find(7));
    vector<int> result = subtree.getInOrderTraversal();
    vector<int> expected = {2, 3, 4};
    assert(result == expected);
    printTestResult("TestExtractSubtree");
}

void testContainsSubtree() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    int subArr[] = {3, 2, 4};
    BinaryTree<int> subtree(subArr, 3);
    assert(tree.containsSubtree(subtree));
    int notSubArr[] = {3, 2, 5};
    BinaryTree<int> notSubtree(notSubArr, 3);
    assert(!tree.containsSubtree(notSubtree));
    printTestResult("TestContainsSubtree");
}

void testMap() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    auto doubler = [](int x) { return 2 * x; };
    BinaryTree<int> mappedTree = tree.map(doubler);
    vector<int> result = mappedTree.getInOrderTraversal();
    vector<int> expected = {4, 6, 8, 10, 12, 14, 16};
    assert(result == expected);
    printTestResult("TestMap");
}

void testWhere() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    BinaryTree<int> tree(arr, 7);
    auto evenPredicate = [](int x) { return x % 2 == 0; };
    BinaryTree<int> filteredTree = tree.where(evenPredicate);
    vector<int> result = filteredTree.getInOrderTraversal();
    vector<int> expected = {2, 4, 6, 8};
    assert(result == expected);
    printTestResult("TestWhere");
}

void testReduce() {
    int arr[] = {5, 3, 8, 1, 4, 7, 10};
    BinaryTree<int> tree(arr, 7);
    int sum = tree.reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 38);
    printTestResult("TestReduce");
}

void testPreOrderTraversalHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    vector<int> preOrder = heap.getPreOrderTraversal();
    vector<int> expectedPreOrder = {8, 10, 17, 15, 20};
    assert(preOrder == expectedPreOrder);
    printTestResult("TestPreOrderTraversalHeap");
}

void testInOrderTraversalHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    vector<int> inOrder = heap.getInOrderTraversal();
    vector<int> expectedInOrder = {17, 10, 15, 8, 20};
    assert(inOrder == expectedInOrder);
    printTestResult("TestInOrderTraversalHeap");
}

void testExtractMinAndPostOrderTraversalHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    int minVal = heap.extractMin();
    assert(minVal == 8);
    vector<int> postOrder = heap.getPostOrderTraversal();
    vector<int> expectedPostOrder = {17, 15, 20, 10};
    assert(postOrder == expectedPostOrder);
    printTestResult("TestExtractMinAndPostOrderTraversalHeap");
}

void testFindElementHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    assert(heap.findElement(15) == true);
    assert(heap.findElement(8) == true);
    printTestResult("TestFindElementHeap");
}

void testMapHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    MinHeap<int> mappedHeap = heap.map([](int x) { return x * 2; });
    vector<int> preOrder = mappedHeap.getPreOrderTraversal();
    vector<int> expectedPreOrder = {16, 20, 34, 30, 40};
    assert(preOrder == expectedPreOrder);
    printTestResult("TestMapHeap");
}

void testWhereHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    MinHeap<int> filteredHeap = heap.where([](int x) { return x > 15; });
    vector<int> preOrder = filteredHeap.getPreOrderTraversal();
    vector<int> expectedPreOrder = {17, 20};
    assert(preOrder == expectedPreOrder);
    printTestResult("TestWhereHeap");
}

void testReduceHeap() {
    int arr[] = {5, 3, 8, 1, 4, 7, 10};
    MinHeap<int> heap(arr, 7);
    int product = heap.reduce([](int a, int b) { return a * b; }, 1);
    assert(product == 33600);
    printTestResult("TestReduceHeap");
}

void testExtractSubtreeHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    MinHeap<int> subtree = heap.extractSubtree(15);
    vector<int> preOrder = subtree.getPreOrderTraversal();
    vector<int> expectedPreOrder = {10, 15, 17};
    assert(preOrder == expectedPreOrder);
    printTestResult("TestExtractSubtreeHeap");
}

void testContainsSubtreeHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    MinHeap<int> subHeap;
    subHeap.insert(8);
    subHeap.insert(10);
    assert(heap.containsSubtree(subHeap) == true);
    MinHeap<int> nonSubHeap;
    nonSubHeap.insert(25);
    assert(heap.containsSubtree(nonSubHeap) == false);
    printTestResult("TestContainsSubtreeHeap");
}

void testToStringHeap() {
    int arr[] = {10, 15, 20, 17, 8};
    MinHeap<int> heap(arr, 5);
    string heapString = heap.toString();
    string expectedString = "8 10 17 15 20 ";
    assert(heapString == expectedString);
    printTestResult("TestToStringHeap");
}

void runBinaryTreeTests() {
    testCopyConstructor();
    testAddAndFind();
    testRemove();
    testInOrderTraversal();
    testPreOrderTraversal();
    testPostOrderTraversal();
    testMerge();
    testExtractSubtree();
    testContainsSubtree();
    testMap();
    testWhere();
    testReduce();
}

void runMinHeapTest() {
    testPreOrderTraversalHeap();
    testInOrderTraversalHeap();
    testExtractMinAndPostOrderTraversalHeap();
    testFindElementHeap();
    testMapHeap();
    testWhereHeap();
    testReduceHeap();
    testExtractSubtreeHeap();
    testContainsSubtreeHeap();
    testToStringHeap();
}
