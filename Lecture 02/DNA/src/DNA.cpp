/* File: DNA.cpp
 *
 * A program for exploring DNA strands.
 */
#include <iostream>
#include <string>
#include <algorithm> // For swap
#include "simpio.h"
#include "strlib.h"  // For toUpperCase
#include "console.h"
using namespace std;

char pairsWith(char one, char two) {
    /* Cute little trick: sort the characters so that one <= two.
     * That means that we only need to check two possible pairs.
     */
    if (one >= two) swap(one, two);

    return (one == 'A' && two == 'T') ||
           (one == 'C' && two == 'G');
}

int main() {
    while (true) {
        string first  = toUpperCase(getLine("The first strand: "));
        string second = toUpperCase(getLine("And the next one: "));

        if (areComplementary(first, second)) {
            cout << "You have found your genetic soul mate!" << endl;
        } else {
            cout << "There's plenty of fish in the gene pool." << endl;
        }

        cout << endl;
    }
}

