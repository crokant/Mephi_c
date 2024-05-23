#pragma once

#include "MutableSequence.h"
#include "ConsoleInput.h"
#include "ImmutableSequence.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

using namespace std;
//in ui the user is only given access to mutable type of sequence
//but the tests check the functionality of all the code


template<class T>
class ConsoleInteraction {
private:
    MutableSequence<T> *sequence;

    ConsoleInteraction<T> *createDynamicArraySeq() {
        int size;
        cout << CYAN << "Enter size of your dynamic array sequence" << RESET << "\n<<";
        consoleInput(size);
        T *items = new T[size];
        cout << CYAN << "Enter elements of the sequence" << RESET << "\n<<";
        for (int i = 0; i < size; ++i) {
            consoleInput(items[i]);
        }
        sequence = new MutableArraySequence<T>(items, size);
        delete[] items;
        return this;
    }

    ConsoleInteraction<T> *createLinkedListSeq() {
        int size;
        cout << CYAN << "Enter size of your linked list sequence" << RESET << "\n<<";
        consoleInput(size);
        T *items = new T[size];
        cout << CYAN << "Enter elements of the sequence" << RESET << "\n<<";
        for (int i = 0; i < size; ++i) {
            consoleInput(items[i]);
        }
        sequence = new MutableListSequence<T>(items, size);
        delete[] items;
        return this;
    }

    ConsoleInteraction<T> *chooseTypeOfSequence() {
        int type;
        cout << CYAN << "Choose type of sequence\n>>1 (for dynamic array sequence)\n>>2 (for linked list sequence)"
             << RESET << "\n<<";
        consoleInput(type);
        switch (type) {
            case 1:
                return createDynamicArraySeq();
            case 2:
                return createLinkedListSeq();
            default:
                cout << "InvalidType. Choose again\n";
                return this;
        }
    }

    void appendItem() {
        T item;
        cout << MAGENTA << "Enter item to list append" << RESET << "\n<<";
        consoleInput(item);
        sequence->append(item);
    }

    void prependItem() {
        T item;
        cout << MAGENTA << "Enter item to list prepend" << RESET << "\n<<";
        consoleInput(item);
        sequence->prepend(item);
    }

    void insertItemAt() {
        int index;
        T item;
        cout << MAGENTA << "Enter index and item to insert" << RESET << "\n<<";
        consoleInput(index);
        consoleInput(item);
        try {
            sequence->insertAt(index, item);
        } catch (const out_of_range &e) {
            cout << "IndexOutOfRange\n";
        }
    }


    void getItemAt() {
        int index;
        cout << MAGENTA << "Enter index to get item" << RESET << "\n<<";
        consoleInput(index);
        try {
            T item = sequence->get(index);
            cout << MAGENTA << "Item at index " << index << " is " << item << RESET << "\n";
        } catch (const out_of_range &e) {
            cout << "IndexOutOfRange\n";
        }
    }

    void getFirstItem() {
        try {
            T item = sequence->getFirst();
            cout << MAGENTA << "First item is " << item << RESET << "\n";
        } catch (const out_of_range &e) {
            cout << "SequenceIsEmpty\n";
        }
    }

    void getLastItem() {
        try {
            T item = sequence->getLast();
            cout << MAGENTA << "Last item is " << item << RESET << "\n";
        } catch (const out_of_range &e) {
            cout << "Sequence is empty\n";
        }
    }

    void getSubSequence() {
        int startIndex, endIndex;
        cout << MAGENTA << "Enter start and end index for subsequence" << RESET << "\n<<";
        consoleInput(startIndex);
        consoleInput(endIndex);
        try {
            auto subsequence = sequence->getSubSequence(startIndex, endIndex);
            delete sequence;
            sequence = subsequence;
            cout << MAGENTA << "Subsequence created" << RESET << "\n";
        } catch (const out_of_range &e) {
            cout << "IndexOutOfRange\n";
        }
    }

    void getSequenceLength() {
        int length = sequence->getLength();
        cout << MAGENTA << "Length of the sequence is " << length << RESET "\n";
    }

    void concatenateSequence() {
        cout << MAGENTA << "Choose type of sequence to concatenate" << RESET << "\n";
        ConsoleInteraction<T> otherConsole;
        otherConsole.chooseTypeOfSequence();
        sequence->concat(otherConsole.sequence);
        cout << MAGENTA << "Sequences concatenated" << RESET << "\n";
    }

    void printSequence() {
        const char *prefix = "(";
        int length = sequence->getLength();
        cout << MAGENTA << "Sequence: ";
        for (int i = 0; i < length; ++i) {
            cout << prefix << sequence->get(i);
            prefix = "; ";
        }
        cout << ")" << RESET << "\n";
    }

    void showMenu() {
        int choice;
        do {
            cout << CYAN << "\nChoose an action:\n"
                            ">>1 Append item\n"
                            ">>2 Prepend item\n"
                            ">>3 Insert item at position\n"
                            ">>4 Get item at position\n"
                            ">>5 Get first item\n"
                            ">>6 Get last item\n"
                            ">>7 Get subsequence\n"
                            ">>8 Get length\n"
                            ">>9 Concatenate with another sequence\n"
                            ">>10 Print sequence\n"
                            ">>11 Exit" << RESET << "\n<<";
            consoleInput(choice);

            switch (choice) {
                case 1:
                    appendItem();
                    break;
                case 2:
                    prependItem();
                    break;
                case 3:
                    insertItemAt();
                    break;
                case 4:
                    getItemAt();
                    break;
                case 5:
                    getFirstItem();
                    break;
                case 6:
                    getLastItem();
                    break;
                case 7:
                    getSubSequence();
                    break;
                case 8:
                    getSequenceLength();
                    break;
                case 9:
                    concatenateSequence();
                    break;
                case 10:
                    printSequence();
                    break;
                case 11:
                    cout << YELLOW << "Exiting menu" << RESET << "\n";
                    break;
                default:
                    cout << "Invalid choice. Please choose again\n";
            }
        } while (choice != 11);
    }

public:
    void run() {
        chooseTypeOfSequence();
        showMenu();
    }
};