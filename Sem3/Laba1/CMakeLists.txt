cmake_minimum_required(VERSION 3.25)
project(LABA1_Mephi_Sem3)

set(CMAKE_CXX_STANDARD 17)

add_executable(LABA1_Mephi_Sem3 main.cpp SharedPtr.h UniquePtr.h WeakPtr.h SmartList.h SmartListSequence.h ../tests/SmartPointersTests.cpp ../tests/SmartListTests.cpp ../tests/LoadTests.cpp ../tests/SmartListSequenceTests.cpp)