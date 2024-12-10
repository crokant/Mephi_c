#include "../UnorderedMap.h"
#include "tests.h"
#include <iostream>

void check(bool condition) {
    if (!condition) {
        throw std::runtime_error("tests failed");
    }
}

void testInsertAndFind() {
    UnorderedMap<std::string, int> map;

    map.insert("Alice", 25);
    map.insert("Bob", 30);

    int value;

    check(map.find("Alice", value) && value == 25);
    check(map.find("Bob", value) && value == 30);
    check(!map.find("Charlie", value));
}

void testContains() {
    UnorderedMap<std::string, int> map;

    map.insert("Alice", 25);

    check(map.contains("Alice"));
    check(!map.contains("Bob"));
}

void testSize() {
    UnorderedMap<std::string, int> map;

    map.insert("Alice", 25);
    map.insert("Bob", 30);

    check(map.size() == 2);
}

void testFind() {
    UnorderedMap<std::string, int> map;

    map.insert("Alice", 25);
    map.insert("Bob", 30);

    int value;

    check(map.find("Alice", value) && value == 25);
    check(map.find("Bob", value) && value == 30);
    check(!map.find("Charlie", value));

    map.insert("Charlie", 40);
    check(map.find("Charlie", value) && value == 40);

    int newValue = 50;
    check(map.find("Charlie", newValue) && newValue == 40);
}

void runMapTests() {
    testInsertAndFind();
    testContains();
    testSize();
    testFind();

    std::cout << "UnorderedMap tests completed!" << std::endl;
}
