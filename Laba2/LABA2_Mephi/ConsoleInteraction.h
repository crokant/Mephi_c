#pragma once

#include "MutableSequence.h"
#include "ConsoleInput.h"

using namespace std;
//in ui the user is only given access to mutable type of sequence
//but the tests check the functionality of all the code


template<class T>
class ConsoleInteraction {
private:
    MutableSequence<T> *sequence;

    ConsoleInteraction<T> *createDynamicArraySeq() {
        int size;
        cout << "Enter size of your dynamic array sequence\n<<";
        consoleInput(size);
        T *items = new T[size];
        cout << "Enter elements of the sequence\n<<";
        for (int i = 0; i < size; ++i) {
            consoleInput(items[i]);
        }
        sequence = new MutableArraySequence<T>(items, size);
        delete[] items;
        return this;
    }

    ConsoleInteraction<T> *createLinkedListSeq() {
        int size;
        cout << "Enter size of your linked list sequence\n<<";
        consoleInput(size);
        T *items = new T[size];
        cout << "Enter elements of the sequence\n<<";
        for (int i = 0; i < size; ++i) {
            consoleInput(items[i]);
        }
        sequence = new MutableListSequence<T>(items, size);
        delete[] items;
        return this;
    }

    ConsoleInteraction<T> *chooseTypeOfSequence() {
        int type;
        cout << "Choose type of sequence\n>>1 (for dynamic array sequence)\n>>2 (for linked list sequence)\n<<";
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
        cout << "Enter item to append\n<<";
        consoleInput(item);
        sequence->append(item);
    }

    void prependItem() {
        T item;
        cout << "Enter item to prepend\n<<";
        consoleInput(item);
        sequence->prepend(item);
    }

    void insertItemAt() {
        int index;
        T item;
        cout << "Enter index and item to insert\n<<";
        consoleInput(index);
        consoleInput(item);
        sequence->insertAt(index, item);
    }

    void getItemAt() {
        int index;
        cout << "Enter index to get item\n<<";
        consoleInput(index);
        try {
            T item = sequence->get(index);
            cout << "Item at index " << index << " is " << item << "\n";
        } catch (const out_of_range &e) {
            cout << "IndexOutOfRange\n";
        }
    }

    void getFirstItem() {
        try {
            T item = sequence->getFirst();
            cout << "First item is " << item << "\n";
        } catch (const out_of_range &e) {
            cout << "SequenceIsEmpty\n";
        }
    }

    void getLastItem() {
        try {
            T item = sequence->getLast();
            cout << "Last item is " << item << "\n";
        } catch (const out_of_range &e) {
            cout << "Sequence is empty\n";
        }
    }

    void getSubSequence() {
        int startIndex, endIndex;
        cout << "Enter start and end index for subsequence\n<<";
        consoleInput(startIndex);
        consoleInput(endIndex);
        try {
            auto subsequence = sequence->getSubSequence(startIndex, endIndex);
            delete sequence;
            sequence = subsequence;
            cout << "Subsequence created.\n";
        } catch (const out_of_range &e) {
            cout << "IndexOutOfRange\n";
        }
    }

    void getSequenceLength() {
        int length = sequence->getLength();
        cout << "Length of the sequence is " << length << "\n";
    }

    void concatenateSequence() {
        cout << "Choose type of sequence to concatenate\n";
        ConsoleInteraction<T> otherConsole;
        otherConsole.chooseTypeOfSequence();
        auto concatenatedSequence = sequence->concat(otherConsole.sequence);
        delete sequence;
        sequence = concatenatedSequence;
        cout << "Sequences concatenated.\n";
    }

    void printSequence() {
        const char *prefix = "(";
        int length = sequence->getLength();
        cout << "Sequence: ";
        for (int i = 0; i < length; ++i) {
            cout << prefix << sequence->get(i);
            prefix = "; ";
        }
        cout << ")\n";
    }

    void showMenu() {
        int choice;
        do {
            cout << "\nChoose an action:\n";
            cout << ">>1 Append item\n";
            cout << ">>2 Prepend item\n";
            cout << ">>3 Insert item at position\n";
            cout << ">>4 Get item at position\n";
            cout << ">>5 Get first item\n";
            cout << ">>6 Get last item\n";
            cout << ">>7 Get subsequence\n";
            cout << ">>8 Get length\n";
            cout << ">>9 Concatenate with another sequence\n";
            cout << ">>10 Print sequence\n";
            cout << ">>11 Exit\n<<";
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
                    cout << "Exiting menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please choose again.\n";
            }
        } while (choice != 11);
    }

public:
    void run() {
        chooseTypeOfSequence();
        showMenu();
    }
};