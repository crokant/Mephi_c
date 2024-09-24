cmake_minimum_required(VERSION 3.25)
project(LABA2_Mephi)

set(CMAKE_CXX_STANDARD 17)

add_executable(LABA2_Mephi main.cpp MutableSequence.h ImmutableSequence.h MutableListSequence.h MutableArraySequence.h LinkedList.h DynamicArray.h ImmutableListSequence.h ImmutableArraySequence.h tests.h tests.cpp ConsoleInteraction.h ConsoleInput.h)
