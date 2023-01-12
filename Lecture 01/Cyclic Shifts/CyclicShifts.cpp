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

bool areCyclicallyEqual(string one, string two);

int main() {
    string one = getLine("First string:  ");
    string two = getLine("Second string: ");

    if (areCyclicallyEqual(one, two)) {
        cout << "Yep!" << endl;
    } else {
        cout << "Nah." << endl;
    }

    return 0;
}

/* Given two strings, are they cyclic shifts of one another? */
bool areCyclicallyEqual(string one, string two) {
    /* Fencepost issue: Cycle one fewer time than there are
     * characters in the string, but check a number of times
     * equal to the number of characters of the string.
     */
    for (int i = 1; i < one.length(); i++) {
        /* They match! */
        if (one == two) {
            return true;
        }

        /* Cycle the second string. */
        two = two.substr(1) + two[0];
    }

    /* One last comparison to see if the final shift did it. */
    return one == two;
}





