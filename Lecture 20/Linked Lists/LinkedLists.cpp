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

int lengthOf(Cell* list) {
    if (list == nullptr) return 0;

    return 1 + lengthOf(list->next);
}

void printList(Cell* list) {
    if (list == nullptr) return;

    cout << list->value << endl;
    printList(list->next);
}

Cell* readList() {
    string text = getLine("Enter next value, or empty string if you're done: ");

    if (text == "") return nullptr;

    Cell* result  = new Cell;
    result->value = text;
    result->next  = readList();
    return result;
}

void deleteList(Cell* list) {
    if (list == nullptr) return;

    deleteList(list->next);
    delete list;
}

int main() {
    Cell* list = readList();

    cout << "The length of this list is " << lengthOf(list) << endl;
    printList(list);
    deleteList(list);

    return 0;
}










/* Things that give logarithms:
 *
 *   1. Repeatedly dividing by a constant.
 *
 *   n  -->   n/2   -->    n/4    -->   ...  ->  1
 *               O(log n) steps.
 *
 *
 *   2. Repeatedly multiplying by a constant
 *
 *   1  ->  2  ->  4  ->  8  -> ... -> n
 *               O(log n) steps.
 *
 *
 *
 *                *          O(n)
 *              /   \
 *            *       *      O(n)
 *           / \     / \
 *          *   *   *   *    O(n)
 *         / \ / \ / \ / \
 *         * * * * * * * *   O(n)
 *
 */




















