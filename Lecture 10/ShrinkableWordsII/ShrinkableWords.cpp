#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
#include "optional.h"
using namespace std;

/* Forms a Vector<string> showing how to shrink a word down to the empty string,
 * if there is a way to do so.
 */
Optional<Vector<string>> shrinkWord(const string& word, const Lexicon& english) {

}

int main() {
    Lexicon english("EnglishWords.txt");
    while (true) {
        string word = getLine("Enter a word: ");

        /* Find a shrinking sequence, if one exists. */
        Optional<Vector<string>> result = shrinkWord(word, english);
        if (result != Nothing) {
            cout << result << endl;
        } else {
            cout << "Nothing to see here, folks; move along." << endl;
        }
    }
}



