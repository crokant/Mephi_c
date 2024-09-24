#pragma once
#include "BinaryTree.h"
#include "BinaryHeap.h"

BinaryTree<int> createTree();

MinHeap<int> createHeap();

void findElementInTree(BinaryTree<int> &tree);

void removeElementFromTree(BinaryTree<int> &tree);

void traverseTree(BinaryTree<int> &tree);

void findElementInHeap(MinHeap<int> &heap);

void traverseHeap(MinHeap<int> &heap);