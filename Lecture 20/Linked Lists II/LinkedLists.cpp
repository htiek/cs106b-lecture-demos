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

/* Given a linked list, how long is it? */
int lengthOf(Cell* list) {
    /* Base case: An empty list has length zero. */
    if (list == nullptr) return 0;

    /* Recursive case: The length is one, plus the length of the
     * remaining list.
     */
    return 1 + lengthOf(list->next);
}

/* From last time! */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << "  " << list->value << endl;
        list = list->next;
    }
}

/* From last time! */
void deleteList(Cell* list) {
    while (list != nullptr) {
        Cell* next = list->next;
        delete list;
        list = next;
    }
}

/* Puts a new item at the front of the list. */
void prependTo(Cell*& list, const string& value) {
    /* Create a new cell. */
    Cell* cell  = new Cell;
    cell->value = value;

    /* This cell needs point to the start of the old list. */
    cell->next = list;

    /* Update the head of the list. */
    list = cell;
}

int main() {
    Cell* list = readList();

    cout << "The list has " << lengthOf(list) << " items. They are: " << endl;
    printList(list);
    cout << "That's all!" << endl;

    deleteList(head);
    return 0;
}






