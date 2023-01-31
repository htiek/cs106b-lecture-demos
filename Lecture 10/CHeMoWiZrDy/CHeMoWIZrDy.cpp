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
    "Sc",  "Ti", "V", "Cr", "Mn",
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

Optional<string> isElementSpellable(const string& word) {
    if (word == "") {
        return "";
    }
    for (string element: kAllElements) {
        if (startsWith(toLowerCase(word), toLowerCase(element))) {
            Optional<string> result = isElementSpellable(word.substr(element.length()));
            if (result != Nothing) {
                return element + result.value();
            }
        }
    }
    return Nothing;
}

int main() {
    Lexicon english("EnglishWords.txt");
    for (string word: english) {
        if (word.length() >= 15) {
            Optional<string> result = isElementSpellable(word);
            if (result != Nothing) {
                cout << result << endl;
            }
        }
    }
    return 0;
}
