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
        list = list->>next;
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

void prependTo(Cell* list, const string& value) {
    // TODO: Write this!
}

int main() {
    Cell* list = nullptr;

    prependTo(list, "Quokka");
    prependTo(list, "Pudu");
    prependTo(list, "Dikdik");

    printList(list);
    deleteList(list);
    return 0;
}




