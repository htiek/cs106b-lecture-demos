/* File: Combinations.cpp
 *
 * Function to list off all combinations of a set.
 */
#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;

void listCombinationsRec(const Set<int>& remaining, int k,
                         const Set<int>& used) {
    /* Base case: If we need zero more elements, just print what we have. */
    if (k == 0) {
        cout << used << endl;
    }
    /* Base case: If there's nothing to pick from and we still need something, or we are
     * asked to pick more elements than exist, then nothing we do will work. It doesn't
     * matter what decisions we've made so far; they can't lead us to anything that works.
     */
    else if (remaining.isEmpty() || remaining.size() < k) {
        return;
    }
    /* Recursive case: Pick an element we haven't considered. We either use it or we don't. */
    else {
        int elem = remaining.first();

        /* Option 1: Exclude this element. */
        listCombinationsRec(remaining - elem, k, used);

        /* Option 2: Include this element. */
        listCombinationsRec(remaining - elem, k - 1, used + elem);
    }
}

void listCombinationsOf(const Set<int>& elems, int k) {
    listCombinationsRec(elems, k, {});
}

int main() {
    listCombinationsOf({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 5);
    return 0;
}
