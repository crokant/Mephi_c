#include "test.h"
#include "../UniquePtr.h"
#include "../SharedPtr.h"
#include "../WeakPtr.h"

#include <iostream>
#include <cassert>

void testUniquePtrBasic() {
    UniquePtr<int> uPtr(new int(10));
    assert(uPtr);
    assert(*uPtr == 10);
    assert(uPtr.get() != nullptr);
}

void testUniquePtrMoveSemantics() {
    UniquePtr<int> uPtr1(new int(5));
    UniquePtr<int> uPtr2 = std::move(uPtr1);
    assert(!uPtr1);
    assert(uPtr2);
    assert(*uPtr2 == 5);
}

void testUniquePtrReset() {
    UniquePtr<int> uPtr(new int(20));
    uPtr.reset(new int(30));
    assert(*uPtr == 30);
    uPtr.reset();
    assert(!uPtr);
}

void testUniquePtrRelease() {
    UniquePtr<int> uPtr(new int(40));
    int *rawPtr = uPtr.release();
    assert(rawPtr != nullptr);
    assert(!uPtr);
    delete rawPtr;
}

void testSharedPtrBasic() {
    SharedPtr<int> sPtr(new int(15));
    assert(*sPtr == 15);
    assert(sPtr.useCount() == 1);
    assert(sPtr.get() != nullptr);
}

void testSharedPtrCopy() {
    SharedPtr<int> sPtr1(new int(25));
    SharedPtr<int> sPtr2 = sPtr1;
    assert(*sPtr1 == 25);
    assert(*sPtr2 == 25);
    assert(sPtr1.useCount() == 2);
    assert(sPtr2.useCount() == 2);
}

void testSharedPtrReset() {
    SharedPtr<int> sPtr(new int(50));
    sPtr.reset();
    assert(!sPtr);
    assert(sPtr.useCount() == 0);
}

void testSharedPtrSwap() {
    SharedPtr<int> sPtr1(new int(60));
    SharedPtr<int> sPtr2(new int(70));
    sPtr1.swap(sPtr2);
    assert(*sPtr1 == 70);
    assert(*sPtr2 == 60);
    assert(sPtr1.useCount() == 1);
    assert(sPtr2.useCount() == 1);
}

void testWeakPtrBasic() {
    SharedPtr<int> sPtr(new int(100));
    WeakPtr<int> wPtr(sPtr);
    assert(wPtr.useCount() == 1);
    assert(!wPtr.expired());
    SharedPtr<int> locked = wPtr.lock();
    assert(locked);
    assert(*locked == 100);
}

void runPointersTests() {
    testUniquePtrBasic();
    testUniquePtrMoveSemantics();
    testUniquePtrReset();
    testUniquePtrRelease();
    testSharedPtrBasic();
    testSharedPtrCopy();
    testSharedPtrReset();
    testSharedPtrSwap();
    testWeakPtrBasic();
    std::cout << "Smart pointer functionality tests passed\n";
}