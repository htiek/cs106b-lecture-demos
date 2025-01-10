/* File: Cyclic Shifts.cpp
 *
 * A program that tests if two strings are cyclic shifts of
 * one another.
 */
#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given two strings, is one a rotation of the other? */
bool areCyclicallyEqual(string one, string two);

int main() {
    /* Get two strings from the user. */
    string one = getLine("First string:  ");
    string two = getLine("Second string: ");

    /* See if one rotates into the other. */
    if (areCyclicallyEqual(one, two)) {
        cout << "Yep!" << endl;
    } else {
        cout << "Nah." << endl;
    }

    return 0;
}





