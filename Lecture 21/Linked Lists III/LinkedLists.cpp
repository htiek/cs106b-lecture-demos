/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very third program using Linked Lists! :-D
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

/* From last time! */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << list->value << endl;
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

/* Works flawlessly. */
void prependTo(Cell*& list, const string& value) {
    Cell* cell  = new Cell;
    cell->value = value;

    cell->next  = list;
    list = cell;
}

/* Beautiful, beautiful code. Should win an award. */
void appendTo(Cell*& list, Cell*& tail, const string& value) {
    Cell* cell  = new Cell;
    cell->value = value;
    cell->next  = nullptr;

    /* One option: The list is empty. */
    if (list == nullptr) {
        list = cell;
    }
    /* Other option: List has at least one cell. */
    else {
        tail->next = cell; // Append the cell to the list
    }
    tail = cell; // Make the tail point to the end of the list.
}

int main() {
    Cell* list = nullptr;
    Cell* tail = nullptr;

    appendTo(list, tail, "Quokka");
    appendTo(list, tail, "Pudu");
    appendTo(list, tail, "Dikdik");
    appendTo(list, tail, "Gerenuk");

    printList(list);
    deleteList(list);
    return 0;
}






