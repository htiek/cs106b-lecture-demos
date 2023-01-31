#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
#include "optional.h"
using namespace std;

Optional<Vector<string>> isShrinkable(const string& word,
                                      const Lexicon& english) {
    /* Base Case: Non-words aren't shrinkable words. */
    if (!english.contains(word)) {
        return Nothing;
    }

    /* Base Case: Any word of length 1 is shrinkable. */
    if (word.length() == 1) {
        return { word };
    }

    /* Recursive step: look at all words you can
     * form by removing a single letter. If any of
     * them are shrinkable, the whole word is
     * shrinkable!
     */
    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) +
                          word.substr(i+1);
        auto result = isShrinkable(shrunken, english);
        if (result != Nothing) {
            result.value() += word;
            return result;
        }
    }

    /* If none of those options worked, this string
     * cannot be shrunk.
     */
    return Nothing;
}

int main() {
    Lexicon english("EnglishWords.txt");
    while (true) {
        string word = getLine("Enter a word: ");

        auto sequence = isShrinkable(word, english);
        if (sequence != Nothing) {
            cout << "It's shrinkable!" << endl;
            for (string step: sequence.value()) {
                cout << step << endl;
            }
        } else {
            cout << "Nothing to see here, folks; move along." << endl;
        }
    }
}
