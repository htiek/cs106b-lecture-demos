/* File: FunWithStrings.cpp
 *
 * A program for playing around with C++ strings!
 */
#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

string reverseOf(string input);

int main() {
    while (true) {
        string text = getLine("Enter some text: ");
        cout << "Behold, it is now \"" << reverseOf(text) << "\"." << endl << endl;
    }
}

string reverseOf(string input) {
    /* Base Case: The reverse of the empty string is the empty
     * string itself.
     */
    if (input == "") {
        return "";
    }
    /* Recursive Case: To reverse a longer string, move the first
     * character to the back, then reverse what remains.
     */
    else {
        return reverseOf(input.substr(1)) + input[0];
    }
}







