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

/* Prints the contents of a linked list recursively. */
void printList(Cell* list) {
    /* Base Case: Empty list, nothing to print! */
    if (list == nullptr) return;

    /* Recursive Case: Print the first element, then the remaining ones. */
    cout << list->value << endl;
    printList(list->next);
}

/* Prints the contents of a linked list in order. */
void printListIteratively(Cell* list) {
    for (Cell* cell = list; cell != nullptr; cell = cell->next) {
        cout << cell->value << endl;
    }
}

/* Recursively reads in a list of values from the user and builds a list out of them.
 * The elements will be in the order in which they were added.
 */
Cell* readList() {
    string line = getLine("Next entry? ");

    /* Base Case: If there's nothing to put in the list, return an empty list. */
    if (line == "") return nullptr;

    /* Recursive Step: Make a new cell with this value, then fill in the rest of
     * the list recursively.
     */
    Cell* result = new Cell;
    result->value = line;
    result->next = readList();
    return result;
}

/* Frees a linked list iteratively. */
void freeListIteratively(Cell* list) {
    while (list != nullptr) {
        Cell* next = list->next;
        delete list;
        list = next;
    }
}

/* Frees a linked list recursively. */
void freeList(Cell* list) {
    if (list == nullptr) return;

    freeList(list->next);
    delete list;
}

/* Prepends a new cell onto the front of a linked list. */
void listInsert(Cell*& list, const string& value) {
    Cell* newCell = new Cell;
    newCell->value = value;
    newCell->next = list;
    list = newCell;
}

int main() {
    Cell* list = readList();
    printList(list);
    freeList(list);
    return 0;
}




