#include <iostream>
#include <stdexcept>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

template<typename T>
class MinHeap {
private:
    vector<T> data;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (data[index] < data[parentIndex]) {
            swap(data[index], data[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index;

        if (leftChildIndex < data.size() && data[leftChildIndex] < data[smallest]) {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < data.size() && data[rightChildIndex] < data[smallest]) {
            smallest = rightChildIndex;
        }

        if (smallest != index) {
            swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

    bool findElement(int index, const T &value) const {
        if (index >= data.size()) return false;
        if (data[index] == value) return true;
        if (data[index] > value) return false;

        return findElement(2 * index + 1, value) || findElement(2 * index + 2, value);
    }

    void preOrderTraversal(int index, vector<T> &result) const {
        if (index >= data.size()) return;
        result.push_back(data[index]);
        preOrderTraversal(2 * index + 1, result);
        preOrderTraversal(2 * index + 2, result);
    }

    void inOrderTraversal(int index, vector<T> &result) const {
        if (index >= data.size()) return;
        inOrderTraversal(2 * index + 1, result);
        result.push_back(data[index]);
        inOrderTraversal(2 * index + 2, result);
    }

    void postOrderTraversal(int index, vector<T> &result) const {
        if (index >= data.size()) return;
        postOrderTraversal(2 * index + 1, result);
        postOrderTraversal(2 * index + 2, result);
        result.push_back(data[index]);
    }

    bool isSubtree(int mainIndex, const MinHeap &subtree, int subIndex) const {
        if (subIndex >= subtree.data.size()) return true;
        if (mainIndex >= data.size() || data[mainIndex] != subtree.data[subIndex]) return false;
        return isSubtree(2 * mainIndex + 1, subtree, 2 * subIndex + 1) &&
               isSubtree(2 * mainIndex + 2, subtree, 2 * subIndex + 2);
    }

    void toString(int index, ostringstream &oss) const {
        if (index >= data.size()) return;
        oss << data[index] << " ";
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
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    T extractMin() {
        if (data.empty()) throw out_of_range("HeapIsEmpty");
        T minValue = data[0];
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
        return minValue;
    }

    bool findElement(const T &value) const {
        return findElement(0, value);
    }

    MinHeap extractSubtree(const T &value) const {
        int index = findElement(value);
        if (index == -1) throw invalid_argument("ElementNotFound");

        MinHeap subtree;
        vector<int> indicesToProcess = {index};
        while (!indicesToProcess.empty()) {
            int currentIndex = indicesToProcess.back();
            indicesToProcess.pop_back();
            if (currentIndex < data.size()) {
                subtree.insert(data[currentIndex]);
                indicesToProcess.push_back(2 * currentIndex + 1);
                indicesToProcess.push_back(2 * currentIndex + 2);
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
        for (int i = 0; i < data.size(); ++i) {
            if (isSubtree(i, subtree, 0)) {
                return true;
            }
        }
        return false;
    }

    vector<T> getPreOrderTraversal() const {
        vector<T> result;
        preOrderTraversal(0, result);
        return result;
    }

    vector<T> getInOrderTraversal() const {
        vector<T> result;
        inOrderTraversal(0, result);
        return result;
    }

    vector<T> getPostOrderTraversal() const {
        vector<T> result;
        postOrderTraversal(0, result);
        return result;
    }

    MinHeap map(function<T(T)> func) const {
        MinHeap newHeap;
        for (const T &value: data) {
            newHeap.insert(func(value));
        }
        return newHeap;
    }

    MinHeap where(function<bool(T)> predicate) const {
        MinHeap newHeap;
        for (const T &value: data) {
            if (predicate(value)) {
                newHeap.insert(value);
            }
        }
        return newHeap;
    }

    T reduce(const function<T(T, T)> &func, T init) const {
        for (const T &value: data) {
            init = func(init, value);
        }
        return init;
    }
};


