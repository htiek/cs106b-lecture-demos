#include <iostream>
#include "hashset.h"
#include "console.h"
using namespace std;

HashSet<HashSet<string>> combinationsRec(const HashSet<string>& set,
                                         int k, // Number of REMAINING items to pick.
                                         const HashSet<string>& chosen) {
    /* Base case: Need zero more people? You're done! */
    if (k == 0) {
        return { chosen };
    }
    /* Base case: Need more people than remain! That's not possible. */
    else if (k > set.size()) {
        return {};
    }
    /* Recursive case: Pick someone and decide whether to include or exclude them. */
    else {
        string person = set.first();
        HashSet<string> remaining = set - person;

        return combinationsRec(remaining, k, chosen) +
               combinationsRec(remaining, k - 1, chosen + person);
    }
}

HashSet<HashSet<string>> combinationsOf(const HashSet<string>& set, int k) {
    return combinationsRec(set, k, {});
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
    cout << "There are " << combinations << " combinations. They are: " << endl;
    for (HashSet<string> combination: combinations) {
        cout << combination << endl;
    }
    return 0;
}
