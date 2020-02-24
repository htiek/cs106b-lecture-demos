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

int main() {
    Cell* list = new Cell;
    list->value = "dikdik!";
    list->next = new Cell;
    list->next->value = "quokka!";
    list->next->next = new Cell;
    list->next->next->value = "pudu!";
    list->next->next->next = nullptr;

    return 0;
}




