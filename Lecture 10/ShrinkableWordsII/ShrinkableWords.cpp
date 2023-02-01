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
    /* Base Case: Non-words aren't shrinkable words. */
    if (!english.contains(word)) {
        return Nothing;
    }

    /* Base Case: Any word of length 1 is shrinkable. */
    if (word.length() == 1) {
        return { word };
    }

    /* Recursive step: look at all words you can form by removing a
     * single letter. If any of them are shrinkable, the whole word is
     * shrinkable!
     */
    for (int i = 0; i < word.length(); i++) {
        /* Drop character i from the word. */
        string shrunken = word.substr(0, i) + word.substr(i+1);

        /* See if the remaining word is shrinkable. */
        Optional<Vector<string>> result = shrinkWord(shrunken, english);

        /* If so, result now holds a shrinking sequence for the shrunken word.
         * Appending our current word then extends what we have to a full shrinking
         * sequence.
         *
         * A great question to ponder: As written, this will actually give us the
         * REVERSE of a shrinking sequence: it'll start with one letter and build up
         * to the full word. Can you see why? How would you change this so that it
         * instead gives a path from the word down to a single letter.
         */
        if (result != Nothing) {
            return result.value() + word;
        }
    }

    /* If none of those options worked, this string cannot shrink down to a single
     * letter.
     */
    return Nothing;
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



