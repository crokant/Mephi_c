#include "ConsoleVisual.h"
#include "../Laba2/LABA2_Mephi/ConsoleInput.h"
#include "Interactions.h"
#include <iostream>

#define MAGENTA "\033[35m"
#define FUCHSIA "\033[38;5;201m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

using namespace std;

void treeOperations(BinaryTree<int> &tree) {
    cout << FUCHSIA <<"\nThis ui is aimed at determining the "
                      "execution speed of methods" << RESET << endl;
    int choice;
    do {
        cout << CYAN << "Choose an operation:\n"
                        ">>1 Test find\n"
                        ">>2 Test remove\n"
                        ">>3 Test traversal\n"
                        ">>4 Exit"
             << RESET << "\n<<";
        consoleInputOne(choice);
        switch (choice) {
            case 1:
                findElementInTree(tree);
                break;
            case 2:
                removeElementFromTree(tree);
                break;
            case 3:
                traverseTree(tree);
                break;
            case 4:
                cout << YELLOW << "Exiting Operations" << RESET << "\n";
                break;
            default:
                cout << "InvalidChoice\n";
        }
    } while (choice != 4);
}

void heapOperations(MinHeap<int> &heap) {
    cout << FUCHSIA <<"\nThis ui is aimed at determining the "
                      "execution speed of methods" << RESET << endl;
    int choice;
    do {
        cout << CYAN << "Choose an operation:\n"
                        ">>1 Test find\n"
                        ">>2 Test traversal\n"
                        ">>3 Exit"
             << RESET << "\n<<";
        consoleInputOne(choice);
        switch (choice) {
            case 1:
                findElementInHeap(heap);
                break;
            case 2:
                traverseHeap(heap);
                break;
            case 3:
                cout << YELLOW << "Exiting vector operations" << RESET << "\n";
                break;
            default:
                cout << "InvalidChoice\n";
        }
    } while (choice != 3);
}

void startMenu() {
    int choice;
    cout << "\nif all tests are passed, you can continue\n";
    do {
        cout << MAGENTA << "\nChoose an option:\n"
                           ">>1 BinaryTree\n"
                           ">>2 BinaryHeap\n"
                           ">>3 Exit"
             << RESET << "\n<<";
        consoleInputOne(choice);
        if (choice == 1) {
            auto tree = createTree();
            treeOperations(tree);
        } else if (choice == 2) {
            auto heap = createHeap();
            heapOperations(heap);
        } else if (choice == 3) {
            cout << YELLOW << "Exiting menu" << RESET << "\n";
        } else {
            cout << "InvalidOption" << endl;
        }
    } while (choice != 3);
}