#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
using namespace std;

bool isShrinkable(const string& word, const Lexicon& english, Vector<string>& sequence) {
    /* Base case 1: Non-words can't be shrinkable words. */
    if (!english.contains(word)) {
        return false;
    }

    /* Base case 2: Any word of length 1 is shrinkable. */
    if (word.length() == 1) {
        sequence += word;
        return true;
    }

    /* Recursive step: look at all words you can form by removing a single letter.
     * If any of them are shrinkable, the whole word is shrinkable!
     */
    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) + word.substr(i+1);
        if (isShrinkable(shrunken, english, sequence)) {
            sequence += word;
            return true;
        }
    }

    /* If none of those options worked, this string cannot be shrunk. */
    return false;
}

int main() {
    Lexicon english("EnglishWords.txt");
    while (true) {
        string word = getLine("Enter a word: ");

        Vector<string> shrinkingSequence;
        if (isShrinkable(word, english, shrinkingSequence)) {
            cout << "It's shrinkable! Here's how:" << endl;
            for (string word: shrinkingSequence) {
                cout << word << endl;
            }
        } else {
            cout << "Nothing to see here, folks; move along." << endl;
        }
    }
}
