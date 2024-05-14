#pragma once

#include <iostream>

template<class T>
void consoleInput(T &target) {
    T copy;
    std::cin >> copy;
    if (std::cin.fail()) {
        throw std::runtime_error("IncorrectInputFormat");
    }
    target = copy;
}