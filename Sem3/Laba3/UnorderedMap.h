#pragma once

#include "../../Sem2/Laba2/LABA2_Mephi/LinkedList.h"
#include "../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"
#include <string>

template <typename K, typename V>
class UnorderedMap {
private:
    struct KeyValuePair {
        K key;
        V value;

        KeyValuePair(const K &k, const V &v) : key(k), value(v) {}
    };

    DynamicArray<LinkedList<KeyValuePair>> table;
    int bucketCount;

    size_t hash(const K &key) const {
        std::hash<K> hasher;
        return hasher(key) % bucketCount;
    }

public:
    explicit UnorderedMap(int size = 10) : bucketCount(size), table(size) {}

    void insert(const K &key, const V &value) {
        size_t index = hash(key);
        LinkedList<KeyValuePair> &bucket = table[index];

        for (int i = 0; i < bucket.getLength(); ++i) {
            if (bucket.getByIndex(i).key == key) {
                bucket.getByIndex(i).value = value;
                return;
            }
        }
        bucket.append(KeyValuePair(key, value));
    }

    bool find(const K &key, V &value) const {
        size_t index = hash(key);
        const LinkedList<KeyValuePair> &bucket = table[index];

        for (int i = 0; i < bucket.getLength(); ++i) {
            if (bucket.getByIndex(i).key == key) {
                value = bucket.getByIndex(i).value;
                return true;
            }
        }
        return false;
    }

    bool contains(const K &key) const {
        V dummy;
        return find(key, dummy);
    }
};
