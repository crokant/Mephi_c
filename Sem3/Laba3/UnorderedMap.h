#pragma once

#include "../../Sem2/Laba2/LABA2_Mephi/LinkedList.h"
#include "../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"
#include <string>
#include <functional>

template<typename K, typename V>
class UnorderedMap {
private:
    struct KeyValuePair {
        K key;
        V value;

        KeyValuePair(const K &k, const V &v) : key(k), value(v) {}
    };

    DynamicArray<LinkedList<KeyValuePair>> table;
    int bucketCount;
    int elementCount;

    size_t hash(const K &key) const {
        std::hash<K> hasher;
        return hasher(key) % bucketCount;
    }

    void rehash() {
        int newBucketCount = bucketCount * 2;
        DynamicArray<LinkedList<KeyValuePair>> newTable(newBucketCount);

        for (int i = 0; i < bucketCount; ++i) {
            LinkedList<KeyValuePair> &bucket = table[i];
            for (int j = 0; j < bucket.getLength(); ++j) {
                KeyValuePair &pair = bucket.getByIndex(j);
                size_t newIndex = std::hash<K>()(pair.key) % newBucketCount;
                newTable[newIndex].append(pair);
            }
        }

        table = std::move(newTable);
        bucketCount = newBucketCount;
    }

public:
    explicit UnorderedMap(int size = 10) : bucketCount(size), table(size), elementCount(0) {}

    void insert(const K &key, const V &value) {
        if (elementCount >= bucketCount * 0.8) {
            rehash();
        }

        size_t index = hash(key);
        LinkedList<KeyValuePair> &bucket = table[index];

        for (int i = 0; i < bucket.getLength(); ++i) {
            if (bucket.getByIndex(i).key == key) {
                bucket.getByIndex(i).value = value;
                return;
            }
        }
        bucket.append(KeyValuePair(key, value));
        ++elementCount;
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

    void erase(const K &key) {
        size_t index = hash(key);
        LinkedList<KeyValuePair> &bucket = table[index];

        for (int i = 0; i < bucket.getLength(); ++i) {
            if (bucket.getByIndex(i).key == key) {
                bucket.removeByIndex(i);
                --elementCount;
                return;
            }
        }
    }

    bool findByIndex(int index, K &key, V &value) const {
        if (index < 0 || index >= elementCount) return false;

        int count = 0;
        for (int i = 0; i < bucketCount; ++i) {
            const LinkedList<KeyValuePair> &bucket = table[i];
            for (int j = 0; j < bucket.getLength(); ++j) {
                if (count == index) {
                    key = bucket.getByIndex(j).key;
                    value = bucket.getByIndex(j).value;
                    return true;
                }
                ++count;
            }
        }
        return false;
    }

    [[nodiscard]] int size() const {
        return elementCount;
    }

    class Iterator {
    private:
        const UnorderedMap<K, V> *map;
        int bucketIndex;
        int itemIndex;

    public:
        Iterator(const UnorderedMap<K, V> *map, int bucketIndex, int itemIndex)
                : map(map), bucketIndex(bucketIndex), itemIndex(itemIndex) {}

        bool operator!=(const Iterator &other) const {
            return bucketIndex != other.bucketIndex || itemIndex != other.itemIndex;
        }

        Iterator &operator++() {
            if (bucketIndex >= map->bucketCount) return *this;

            ++itemIndex;
            if (itemIndex >= map->table[bucketIndex].getLength()) {
                itemIndex = 0;
                ++bucketIndex;
                while (bucketIndex < map->bucketCount && map->table[bucketIndex].getLength() == 0) {
                    ++bucketIndex;
                }
            }
            return *this;
        }

        const K &key() const {
            return map->table[bucketIndex].getByIndex(itemIndex).key;
        }

        const V &value() const {
            return map->table[bucketIndex].getByIndex(itemIndex).value;
        }
    };

    Iterator begin() const {
        int bucketIndex = 0;
        while (bucketIndex < bucketCount && table[bucketIndex].getLength() == 0) {
            ++bucketIndex;
        }
        return Iterator(this, bucketIndex, 0);
    }

    Iterator end() const {
        return Iterator(this, bucketCount, 0);
    }
};
