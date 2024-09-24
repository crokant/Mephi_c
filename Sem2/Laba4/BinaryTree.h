#include <sstream>
#include <functional>
#include <stdexcept>
#include "../Laba2/LABA2_Mephi/DynamicArray.h"

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node *left;
    Node *right;

    explicit Node(const T &value) : data{value}, left{nullptr}, right{nullptr} {}

    Node(const T &value, Node<T> *left, Node<T> *right) : data{value}, left{left}, right{right} {}

    explicit Node(const Node<T> *other) : data{other->data}, left{other->left}, right{other->right} {}
};

template<typename T>
class BinaryTree {
private:
    Node<T> *root;

    void addNode(Node<T> *&node, const T &value) {
        if (!node) {
            node = new Node<T>(value);
        } else if (value < node->data) {
            addNode(node->left, value);
        } else {
            addNode(node->right, value);
        }
    }

    bool findNode(Node<T> *node, const T &value) const {
        if (!node) {
            return false;
        } else if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return findNode(node->left, value);
        } else {
            return findNode(node->right, value);
        }
    }

    Node<T> *findMin(Node<T> *node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void removeNode(Node<T> *&node, const T &value) {
        if (!node) {
            throw invalid_argument("ValueNotFound");
        }
        if (value < node->data) {
            removeNode(node->left, value);
        } else if (value > node->data) {
            removeNode(node->right, value);
        } else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            } else if (!node->left) {
                Node<T> *temp = node->right;
                delete node;
                node = temp;
            } else if (!node->right) {
                Node<T> *temp = node->left;
                delete node;
                node = temp;
            } else {
                Node<T> *temp = findMin(node->right);
                node->data = temp->data;
                removeNode(node->right, temp->data);
            }
        }
    }

    void destroyTree(Node<T> *&node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
            node = nullptr;
        }
    }

    Node<T> *copyTree(Node<T> *node) const {
        if (!node) {
            return nullptr;
        }
        auto *newNode = new Node<T>(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    Node<T> *mapTree(Node<T> *node, const function<T(T)> &func) const {
        if (!node) {
            return nullptr;
        }
        auto *newNode = new Node<T>(func(node->data));
        newNode->left = mapTree(node->left, func);
        newNode->right = mapTree(node->right, func);
        return newNode;
    }

    Node<T> *whereTree(Node<T> *node, const function<bool(T)> &predicate) {
        if (!node) {
            return nullptr;
        }

        Node<T> *newNode = nullptr;
        if (predicate(node->data)) {
            newNode = new Node<T>(node->data);
            newNode->left = whereTree(node->left, predicate);
            newNode->right = whereTree(node->right, predicate);
        } else {
            Node<T> *newLeft = whereTree(node->left, predicate);
            Node<T> *newRight = whereTree(node->right, predicate);
            mergeInto(newNode, newLeft);
            mergeInto(newNode, newRight);
        }

        return newNode;
    }

    T reduceTree(Node<T> *node, const function<T(T, T)> &func, T init) const {
        if (!node) {
            return init;
        }
        T left_result = reduceTree(node->left, func, init);
        T right_result = reduceTree(node->right, func, init);
        return func(node->data, func(left_result, right_result));
    }

    void mergeInto(Node<T> *&head, Node<T> *node) {
        if (!node) {
            return;
        }
        addNode(head, node->data);
        mergeInto(head, node->left);
        mergeInto(head, node->right);
    }

    Node<T> *mergeTrees(Node<T> *root1, Node<T> *root2) {
        if (!root1) {
            return copyTree(root2);
        }
        if (!root2) {
            return copyTree(root1);
        }
        Node<T> *newRoot = copyTree(root1);
        mergeInto(newRoot, root2);
        return newRoot;
    }


    Node<T> *findSubtree(Node<T> *node, const T &value) const {
        if (!node) {
            return nullptr;
        } else if (value == node->data) {
            return node;
        } else if (value < node->data) {
            return findSubtree(node->left, value);
        } else {
            return findSubtree(node->right, value);
        }
    }

    bool equal(Node<T> *node1, Node<T> *node2) const {
        if (node1 == nullptr && node2 == nullptr) return true;
        if (node1 == nullptr || node2 == nullptr) return false;
        if (node1->data != node2->data) return false;
        return equal(node1->left, node2->left) && equal(node1->right, node2->right);
    }

    bool isSubtree(Node<T> *tree, Node<T> *subtree) const {
        if (!subtree) {
            return true;
        }
        if (!tree) {
            return false;
        }
        if (equal(tree, subtree)) {
            return true;
        }
        return isSubtree(tree->left, subtree) || isSubtree(tree->right, subtree);
    }

    void toString(Node<T> *node, ostringstream &oss) const {
        if (node) {
            oss << node->data << " ";
            toString(node->left, oss);
            toString(node->right, oss);
        }
    }

    void preOrderTraversal(Node<T> *node, DynamicArray<T> &result, bool reverse = false) const {
        if (node) {
            result.add(node->data);
            if (reverse) {
                preOrderTraversal(node->right, result, reverse);
                preOrderTraversal(node->left, result, reverse);
            } else {
                preOrderTraversal(node->left, result, reverse);
                preOrderTraversal(node->right, result, reverse);
            }
        }
    }

    void postOrderTraversal(Node<T> *node, DynamicArray<T> &result, bool reverse = false) const {
        if (node) {
            if (reverse) {
                postOrderTraversal(node->right, result, reverse);
                postOrderTraversal(node->left, result, reverse);
            } else {
                postOrderTraversal(node->left, result, reverse);
                postOrderTraversal(node->right, result, reverse);
            }
            result.add(node->data);
        }
    }

    void inOrderTraversal(Node<T> *node, DynamicArray<T> &result, bool reverse = false) const {
        if (node) {
            if (reverse) {
                inOrderTraversal(node->right, result, reverse);
                result.add(node->data);
                inOrderTraversal(node->left, result, reverse);
            } else {
                inOrderTraversal(node->left, result, reverse);
                result.add(node->data);
                inOrderTraversal(node->right, result, reverse);
            }
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree<T> &other) {
        root = copyTree(other.root);
    }

    BinaryTree(const T *array, size_t size) : root(nullptr) {
        for (size_t i = 0; i < size; ++i) {
            add(array[i]);
        }
    }

    ~BinaryTree() {
        destroyTree(root);
    }

    void add(const T &value) {
        addNode(root, value);
    }

    bool find(const T &value) const {
        return findNode(root, value);
    }

    void remove(const T &value) {
        removeNode(root, value);
    }

    BinaryTree<T> map(const function<T(T)> &func) const {
        BinaryTree<T> newTree;
        newTree.root = mapTree(root, func);
        return newTree;
    }

    BinaryTree<T> where(const function<bool(T)> &predicate) {
        BinaryTree<T> newTree;
        newTree.root = whereTree(root, predicate);
        return newTree;
    }

    T reduce(const function<T(T, T)> &func, T init) const {
        return reduceTree(root, func, init);
    }

    BinaryTree<T> merge(const BinaryTree<T> &other) {
        BinaryTree<T> newTree;
        newTree.root = mergeTrees(root, other.root);
        return newTree;
    }

    BinaryTree<T> extractSubtree(const T &value) const {
        BinaryTree<T> subtree;
        subtree.root = copyTree(findSubtree(root, value));
        return subtree;
    }

    bool containsSubtree(const BinaryTree<T> &subtree) const {
        return isSubtree(root, subtree.root);
    }

    bool isEqual(const BinaryTree &other) const {
        return equal(this->root, other.root);
    }

    string toString() const {
        ostringstream oss;
        toString(root, oss);
        return oss.str();
    }

    DynamicArray<T> getInOrderTraversal(bool reverse = false) const {
        DynamicArray<T> result;
        inOrderTraversal(root, result, reverse);
        return result;
    }

    DynamicArray<T> getPreOrderTraversal(bool reverse = false) const {
        DynamicArray<T> result;
        preOrderTraversal(root, result, reverse);
        return result;
    }

    DynamicArray<T> getPostOrderTraversal(bool reverse = false) const {
        DynamicArray<T> result;
        postOrderTraversal(root, result, reverse);
        return result;
    }
};