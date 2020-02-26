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

/* Given a linked list, returns the length of that list. */
int lengthOf(Cell* list) {
    /* Base Case: The empty list has length zero. */
    if (list == nullptr) return 0;

    /* Recursive Case: If there's a cell at the front of the list, the list
     * has length 1 (for that cell) plus the length of the rest of the list.
     */
    return 1 + lengthOf(list->next);
}

/* Prints the contents of a linked list, in order. */
void printList(Cell* list) {
    /* Base Case: There's nothing to print if the list is empty. */
    if (list == nullptr) return;

    /* Recursive Case: Print the first cell, then the rest of the list.
     * Question to ponder: What happens if we swap the next two lines, and why? */
    cout << list->value << endl;
    printList(list->next);
}

/* Reads a linked list from the user one element at a time, stopping when
 * the user enters an empty list.
 */
Cell* readList() {
    /* Get a value from the user. */
    string line = getLine("Enter next element: ");

    /* Base Case: The empty list means "we're done." */
    if (line == "") return nullptr;

    /* Recursive Case: This is the first element of the list. What's the
     * rest of it?
     */
    Cell* result = new Cell;
    result->value = line;
    result->next = readList();
    return result;
}

/* Frees all the memory used by a linked list. */
void deleteList(Cell* list) {
    /* Base Case: If the list is empty, there's nothing to do. */
    if (list == nullptr) return;

    /* Recursive Case: Delete the rest of the list, then the first cell.
     *
     * Question to ponder: Why is it a Bad Thing to reorder these lines?
     */
    deleteList(list->next);
    delete list;
}

/* Returns a list of the given length. */
Cell* listOfLength(int n) {
    Cell* result = nullptr;
    for (int i = 0; i < n; i++) {
        Cell* newCell = new Cell;
        newCell->value = to_string(i);
        newCell->next = result;
        result = newCell;
    }
    return result;
}

int main() {
    Cell* list = listOfLength(500000);

    cout << "This list contains " << lengthOf(list) << " cells." << endl;
    printList(list);
    deleteList(list);

    return 0;
}




