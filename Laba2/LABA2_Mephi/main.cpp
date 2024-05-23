#include <iostream>
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "ConsoleInteraction.h"
#include "ConsoleInput.h"
#include "tests.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;

void startMenu() {
    int dataType;
    cout << "if all tests are passed, you can continue\n";
    cout << CYAN << "Choose data type:\n>>1 (for int)\n>>2 (for double)\n>>3 (for char)\n" << RESET << "<<";
    consoleInput(dataType);
    if (dataType == 1) {
        auto *console = new ConsoleInteraction<int>;
        console->run();
    } else if (dataType == 2) {
        auto *console = new ConsoleInteraction<double>;
        console->run();
    } else if (dataType == 3) {
        auto *console = new ConsoleInteraction<char>;
        console->run();
    } else cout << "invalidType";
}


int main() {
    test_dynamic_array();
    test_linked_list();
    test_immutable_array_sequence();
    test_mutable_array_sequence();
    test_immutable_linked_list();
    test_mutable_linked_list();
    startMenu();
}
