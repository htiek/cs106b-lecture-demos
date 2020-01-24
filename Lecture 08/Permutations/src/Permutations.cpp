/* File: Permutations.cpp
 *
 * Functions to list off all permutations of a collection of elements.
 */
#include <iostream>
#include <string>
#include "hashset.h"
#include "console.h"
using namespace std;

void listPermutationsRec(const string& str, const string& chosen) {
    /* Base case: If we have no remaining letters to pick from, print out the order we've
     * come up with so far.
     */
    if (str == "") {
        cout << chosen << endl;
    }
    /* Recursive case: Some character from the string needs to come first. Try all possible
     * ways of choosing what comes next.
     */
    else {
        for (int i = 0; i < str.size(); i++) {
            /* The first argument here is "everything from the string remaining except for
             * character i. Why? That first bit means "everything up to, but not including,
             * element i. That second one means "everything after element i."
             */
            listPermutationsRec(str.substr(0, i) + str.substr(i + 1),
                                chosen + str[i]);
        }
    }
}

void listPermutationsOf(const string& str) {
    listPermutationsRec(str, "");
}

HashSet<string> permutationsRec(const string& str, const string& chosen) {
    if (str == "") {
        return { chosen };
    } else {
        HashSet<string> result;
        for (int i = 0; i < str.size(); i++) {
            result += permutationsRec(str.substr(0, i) + str.substr(i + 1),
                                      chosen + str[i]);
        }
        return result;
    }
}

HashSet<string> permutationsOf(const string& str) {
    return permutationsRec(str, "");
}

int main() {
    HashSet<string> p = permutationsOf("AHI");
    for (string permutation: p) {
        cout << permutation << endl;
    }

    return 0;
}
