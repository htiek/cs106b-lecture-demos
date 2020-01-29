#include <iostream>
#include "hashset.h"
#include "console.h"
using namespace std;


















HashSet<HashSet<string>> combinationsRec(const HashSet<string>& elems,
                                         int k, // How many MORE things to pick
                                         const HashSet<string>& chosen) {
    /* Base case 1: No more to pick? Then you're done. */
    if (k == 0) {
        return { chosen };
    }
    /* Base case 2: Can't find enough people? Sad times! */
    else if (elems.size() < k) {
        return { };
    }
    /* Recursive case: Pick someone, then either include or exclude. */
    else {
        string elem = elems.first();
        HashSet<string> remaining = elems - elem;

        /* Option 1: Include this person. */
        auto with = combinationsRec(remaining, k - 1, chosen + elem);

        /* Option 2: Exclude this person. */
        auto without = combinationsRec(remaining, k, chosen);

        return with + without;
    }
}


HashSet<HashSet<string>> combinationsOf(const HashSet<string>& elems, int k) {
    return combinationsRec(elems, k, {});
}



int main() {
    HashSet<string> usSupremeCourt = {
        "Thomas",
        "Ginsburg",
        "Breyer",
        "Roberts",
        "Alito",
        "Sotomayor",
        "Kagan",
        "Gorsuch",
        "Kavanaugh"
    };

    HashSet<HashSet<string>> combinations = combinationsOf(usSupremeCourt, 5);
    cout << "There are " << combinations.size() << " combinations. They are: " << endl;
    for (HashSet<string> combination: combinations) {
        cout << combination << endl;
    }
    return 0;
}
