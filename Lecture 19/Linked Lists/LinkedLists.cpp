/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very first program using Linked Lists! :-D
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

/* Creates and returns the linked list from the lecture slides:
 *
 * pudu -> quokka -> dikdik -> (nullptr)
 */
Cell* makeList() {
    Cell* list = new Cell;
    list->value = "pudu!";
    list->next = new Cell;
    list->next->value = "quokka!";
    list->next->next = new Cell;
    list->next->next->value = "dikdik!";
    list->next->next->next = nullptr;
    return list;
}

int lengthOf(Cell* list) {
    return -1;
}

int main() {
    Cell* list = makeList();
    cout << "This list has " << lengthOf(list) << " items." << endl;
    return 0;
}
