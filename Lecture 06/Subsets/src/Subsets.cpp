/* File: subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

void listSubsetsRec(const Set<int>& remaining, const Set<int>& picked) {
    if (remaining.isEmpty()) {
        cout << picked << endl;
    } else {
        int elem = remaining.first();

        listSubsetsRec(remaining - elem, picked);
        listSubsetsRec(remaining - elem, picked + elem);
    }
}

void listSubsetsOf(const Set<int>& s) {
    listSubsetsRec(s, {});
}

int main() {
    listSubsetsOf({1, 2, 3, 4, 5});
    return 0;
}

