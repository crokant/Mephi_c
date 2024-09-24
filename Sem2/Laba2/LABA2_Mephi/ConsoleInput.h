#pragma once

#include <iostream>
#include <stdexcept>
#include <limits>

#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;


template<class T>
void consoleInput(T &target) {
    T copy;
    cin >> copy;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << YELLOW << "Try again: " << RESET;
        cin >> copy;
    }
    target = copy;
}

template<class T>
void consoleInputOne(T &target) {
    T copy;
    cin >> copy;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << YELLOW << "Try again: " << RESET;
        cin >> copy;
    }
    target = copy;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
