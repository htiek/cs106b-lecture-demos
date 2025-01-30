#include <iostream>
#include <string>
#include "set.h"
#include "strlib.h"
#include "lexicon.h"
#include "simpio.h"
#include "console.h"
#include "optional.h"
using namespace std;

/* All the elements. */
const Set<string> kAllElements = {
    "H",  "He", "Li", "Be", "B",
    "C",  "N",  "O",  "F",  "Ne",
    "Na", "Mg", "Al", "Si", "P",
    "S",  "Cl", "Ar", "K",  "Ca",
    "Sc", "Ti", "V",  "Cr", "Mn",
    "Fe", "Co", "Ni", "Cu", "Zn",
    "Ga", "Ge", "As", "Se", "Br",
    "Kr", "Rb", "Sr", "Y",  "Zr",
    "Nb", "Mo", "Tc", "Ru", "Rh",
    "Pd", "Ag", "Cd", "In", "Sn",
    "Sb", "Te", "I",  "Xe", "Cs",
    "Ba", "La", "Ce", "Pr", "Nd",
    "Pm", "Sm", "Eu", "Gd", "Tb",
    "Dy", "Ho", "Er", "Tm", "Yb",
    "Lu", "Hf", "Ta", "W",  "Re",
    "Os", "Ir", "Pt", "Au", "Hg",
    "Tl", "Pb", "Bi", "Po", "At",
    "Rn", "Fr", "Ra", "Ac", "Th",
    "Pa", "U",  "Np", "Pu", "Am",
    "Cm", "Bk", "Cf", "Es", "Fm",
    "Md", "No", "Lr", "Rf", "Db",
    "Sg", "Bh", "Hs", "Mt", "Ds",
    "Rg", "Cn", "Nh", "Fl", "Mc",
    "Lv", "Ts", "Og"
};

/* Given a string, finds a way to spell it with element symbols from the
 * periodic table, or returns that there's no way to do this.
 */
Optional<string> spellWithElements(const string& word) {

}

int main() {
    Lexicon english("EnglishWords.txt");

    /* Find all element-spellable words of 15 or more characters. Why 15? Because
     * it's more fun that way. :-)
     */
    for (string word: english) {
        if (word.length() >= 15) {
            /* See if the word can be spelled with elements. */
            Optional<string> result = spellWithElements(word);
            if (result != Nothing) {
                cout << result << endl;
            }
        }
    }
    return 0;
}
