#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;




/* Current members of the US Supreme Court, ordered
 * by seniority. (Or at least, they're ordered HERE
 * by seniority; the Set will order them internally
 * however it feels like it. ^_^)
 *
 * Fun fact: the most junior Associate Justice is
 * responsible for, among other things, opening the
 * door for the other justices and coordinating
 * what's in their cafeteria.
 *
 * Fun fact: The Chief Justice sits, ex officio,
 * on the Board of Regents of the Smithsonian
 * Institution. Job perks!
 */
const Set<string> usSupremeCourt = {
    "Roberts",
    "Thomas",
    "Alito",
    "Sotomayor",
    "Kagan",
    "Gorsuch",
    "Kavanaugh",
    "Barrett",
    "Jackson"
};

int main() {
    Set<Set<string>> combinations = combinationsOf(usSupremeCourt, 5);

    cout << "There are " << combinations.size()
         << " combinations. They are: " << endl;

    for (Set<string> combination: combinations) {
        cout << combination << endl;
    }
    return 0;
}
