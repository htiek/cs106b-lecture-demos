#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;

/*
 * { "Roberts", "Breyer", "Alito", "Thomas", "Kagan" }
 *     ^
 *     |
 *     +------ Set<string>
 *
 * {
 *   { "Roberts", "Breyer", "Alito", "Thomas", "Kagan" },
 *   { "Sotomayor", "Barrett", "Kavanaugh", "Gorsuch", "Roberts" },
 *   ...
 * } <----- Set<Set<string>>, Vector<Set<string>>
 */

Set<Set<string>>
   combinationsRec(const Set<string>& elems,
                   int numRemaining,
                   const Set<string>& soFar) {
    /* Base Case: If we don't need to pick any more
     * people, then we're done!
     */
    if (numRemaining == 0) {
        return { soFar };
    }
    /* Base Case: If we're asked to pick more people
     * than remain, then we can't find any solutions.
     */
    else if (numRemaining > elems.size()) {
        return { };
    }
    /* Recursive Case: Pick a person and decide what to
     * do with them.
     */
    else {
        string elem = elems.first();
        Set<string> remaining = elems - elem;

        /* Option 1: Exclude this person. */
        auto without = combinationsRec(remaining,
                                       numRemaining,
                                       soFar);

        /* Option 2: Include this person. */
        auto with = combinationsRec(remaining,
                                    numRemaining - 1,
                                    soFar + elem);

        return with + without;
    }
}

Set<Set<string>> combinationsOf(const Set<string>& elems,
                                int numToPick) {
    /* Check validity. */
    if (numToPick < 0) {
        error("You shouldn't ask for a negative number of people.");
    }

    return combinationsRec(elems, numToPick, {});
}















/* Current members of the US Supreme Court, ordered
 * by seniority.
 */
const Set<string> usSupremeCourt = {
    "Roberts",
    "Thomas",
    "Breyer",
    "Alito",
    "Sotomayor",
    "Kagan",
    "Gorsuch",
    "Kavanaugh",
    "Barrett"
};

int main() {
    auto combinations = combinationsOf(usSupremeCourt, 5);

    cout << "There are " << combinations.size()
         << " combinations. They are: " << endl;

    for (auto combination: combinations) {
        cout << combination << endl;
    }
    return 0;
}
