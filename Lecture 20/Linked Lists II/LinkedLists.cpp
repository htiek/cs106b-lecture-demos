/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very second program using Linked Lists! :-D
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Cell
 *
 * A cell in a linked list.
 */
struct Cell {
    string value;
    Cell* next;
};

/* Given a linked list, returns the length of that list. */
int lengthOf(Cell* list) {
    int result = 0;
    while (list != nullptr) {
        result++;
        list = list->next;
    }
    return result;
}

/* Prints the contents of a linked list, in order. */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << list->value << endl;
        list = list->next;
    }
}

/* Frees all the memory used by a linked list. */
void deleteList(Cell* list) {
    while (list != nullptr) {
        Cell* next = list->next;
        delete list;
        list = next;
    }
}

/* Reads a linked list from the user one element at a time, stopping when
 * the user enters an empty list.
 */
Cell* readList() {
    Cell* result = nullptr;

    while (true) {
        string line = getLine("Next entry: ");
        if (line == "") break;

        Cell* cell = new Cell;
        cell->value = line;

        cell->next = result;
        result = cell;
    }

    return result;
}

/* Returns a list of the given length. */
Cell* listOfLength(int n) {
    Cell* result = nullptr;
    for (int i = 0; i < n; i++) {
        Cell* newCell = new Cell;
        newCell->value = to_string(n - 1 - i);
        newCell->next = result;
        result = newCell;
    }
    return result;
}

int main() {
    Cell* list = readList();

    cout << "This list contains " << lengthOf(list) << " cells." << endl;
    printList(list);
    deleteList(list);

    return 0;
}




