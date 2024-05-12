cmake_minimum_required(VERSION 3.25)
project(LABA2_Mephi)

set(CMAKE_CXX_STANDARD 17)

add_executable(LABA2_Mephi main.cpp MutableSequence.h MutableListSequence.h MutableArraySequence.h LinkedList.h DynamicArray.h ImmutableListSequence.h ImmutableArraySequence.h ImmutableSequence.h tests.h tests.cpp)
