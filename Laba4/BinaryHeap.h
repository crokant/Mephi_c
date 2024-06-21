#include <iostream>
#include <stdexcept>
#include <functional>
#include <sstream>
#include "../Laba2/LABA2_Mephi/DynamicArray.h"

using namespace std;

template<typename T>
class MinHeap {
private:
    DynamicArray<T> data;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (data.getByIndex(index) < data.getByIndex(parentIndex)) {
            swap(data.getByIndex(index), data.getByIndex(parentIndex));
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index;
        if (leftChildIndex < data.getSize() && data.getByIndex(leftChildIndex) < data.getByIndex(smallest)) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < data.getSize() && data.getByIndex(rightChildIndex) < data.getByIndex(smallest)) {
            smallest = rightChildIndex;
        }
        if (smallest != index) {
            swap(data.getByIndex(index), data.getByIndex(smallest));
            heapifyDown(smallest);
        }
    }

    int findElement(int index, const T &value) const {
        if (index >= data.getSize()) return -1;
        if (data.getByIndex(index) == value) return index;
        if (data.getByIndex(index) > value) return -1;
        return findElement(2 * index + 1, value) || findElement(2 * index + 2, value);
    }

    void preOrderTraversal(int index, DynamicArray<T> &result) const {
        if (index >= data.getSize()) return;
        result.add(data.getByIndex(index));
        preOrderTraversal(2 * index + 1, result);
        preOrderTraversal(2 * index + 2, result);
    }

    void inOrderTraversal(int index, DynamicArray<T> &result) const {
        if (index >= data.getSize()) return;
        inOrderTraversal(2 * index + 1, result);
        result.add(data.getByIndex(index));
        inOrderTraversal(2 * index + 2, result);
    }

    void postOrderTraversal(int index, DynamicArray<T> &result) const {
        if (index >= data.getSize()) return;
        postOrderTraversal(2 * index + 1, result);
        postOrderTraversal(2 * index + 2, result);
        result.add(data.getByIndex(index));
    }

    bool isSubtree(int mainIndex, const MinHeap &subtree, int subIndex) const {
        if (subIndex >= subtree.data.getSize()) return true;
        if (mainIndex >= data.getSize() || data.getByIndex(mainIndex) != subtree.data.getByIndex(subIndex))
            return false;
        return isSubtree(2 * mainIndex + 1, subtree, 2 * subIndex + 1) &&
               isSubtree(2 * mainIndex + 2, subtree, 2 * subIndex + 2);
    }

    void toString(int index, ostringstream &oss) const {
        if (index >= data.getSize()) return;
        oss << data.getByIndex(index) << " ";
        toString(2 * index + 1, oss);
        toString(2 * index + 2, oss);
    }

public:
    MinHeap() {}

    MinHeap(const T *array, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            insert(array[i]);
        }
    }

    MinHeap(const MinHeap<T> &other) : data(other.data) {}

    void insert(const T &value) {
        data.add(value);
        heapifyUp(data.getSize() - 1);
    }

    T extractMin() {
        if (data.getSize() == 0) throw out_of_range("HeapIsEmpty");
        T minValue = data.getByIndex(0);
        data.set(0, data.getByIndex(data.getSize() - 1));
        data.setSize(data.getSize() - 1);
        heapifyDown(0);
        return minValue;
    }

    bool find(const T &value) const {
        return findElement(0, value) != -1;
    }

    MinHeap extractSubtree(const T &value) const {
        int index = findElement(0, value);
        if (index == -1) throw invalid_argument("ElementNotFound");

        MinHeap subtree;
        DynamicArray<int> indicesToProcess;
        indicesToProcess.add(index);
        while (indicesToProcess.getSize() > 0) {
            int currentIndex = indicesToProcess.getByIndex(indicesToProcess.getSize() - 1);
            indicesToProcess.setSize(indicesToProcess.getSize() - 1);
            if (currentIndex < data.getSize()) {
                subtree.insert(data.getByIndex(currentIndex));
                indicesToProcess.add(2 * currentIndex + 1);
                indicesToProcess.add(2 * currentIndex + 2);
            }
        }
        return subtree;
    }

    string toString() const {
        ostringstream oss;
        toString(0, oss);
        return oss.str();
    }

    bool containsSubtree(const MinHeap &subtree) const {
        for (int i = 0; i < data.getSize(); ++i) {
            if (isSubtree(i, subtree, 0)) {
                return true;
            }
        }
        return false;
    }

    DynamicArray<T> getPreOrderTraversal() const {
        DynamicArray<T> result;
        preOrderTraversal(0, result);
        return result;
    }

    DynamicArray<T> getInOrderTraversal() const {
        DynamicArray<T> result;
        inOrderTraversal(0, result);
        return result;
    }

    DynamicArray<T> getPostOrderTraversal() const {
        DynamicArray<T> result;
        postOrderTraversal(0, result);
        return result;
    }

    MinHeap map(function<T(T)> func) const {
        MinHeap newHeap;
        for (int i = 0; i < data.getSize(); ++i) {
            newHeap.insert(func(data.getByIndex(i)));
        }
        return newHeap;
    }

    MinHeap where(function<bool(T)> predicate) const {
        MinHeap newHeap;
        for (int i = 0; i < data.getSize(); ++i) {
            if (predicate(data.getByIndex(i))) {
                newHeap.insert(data.getByIndex(i));
            }
        }
        return newHeap;
    }

    T reduce(const function<T(T, T)> &func, T init) const {
        for (int i = 0; i < data.getSize(); ++i) {
            init = func(init, data.getByIndex(i));
        }
        return init;
    }
};
