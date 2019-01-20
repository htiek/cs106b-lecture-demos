/* File: Permutations.cpp
 *
 * Functions to list off all permutations of a collection of elements.
 */
#include <iostream>
#include <string>
#include "console.h"
using namespace std;

void listPermutationsRec(const string& remaining, const string& used) {
    /* Base case: If we have no remaining letters to pick from, print out the order we've
     * come up with so far.
     */
    if (remaining == "") {
        cout << used << endl;
    }
    /* Recursive case: Some character from the string needs to come first. Try all possible
     * ways of choosing what comes next.
     */
    else {
        for (int i = 0; i < remaining.size(); i++) {
            /* The first argument here is "everything from the string remaining except for
             * character i. Why? That first bit means "everything up to, but not including,
             * element i. That second one means "everything after element i."
             */
            listPermutationsRec(remaining.substr(0, i) + remaining.substr(i + 1),
                                used + remaining[i]);
        }
    }
}

void listPermutationsOf(const string& str) {
    listPermutationsRec(str, "");
}

int main() {
    listPermutationsOf("AHI");

    return 0;
}
