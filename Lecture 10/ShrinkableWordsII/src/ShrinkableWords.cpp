/* File: ShrinkableWords.cpp
 *
 * A program to list off all long shrinkable words in English.
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
using namespace std;

bool isShrinkable(const string& word, const Lexicon& english, Vector<string>& shrinkingSequence) {
    /* Base case 1: Non-words can't be shrinkable words. */
    if (!english.contains(word)) return false;

    /* Base case 2: Any word of length 1 is shrinkable. */
    if (word.length() == 1) {
        shrinkingSequence.add(word);
        return true;
    }

    /* Recursive step: look at all words you can form by removing a single letter.
     * If any of them are shrinkable, the whole word is shrinkable!
     */
    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) + word.substr(i+1);
        if (isShrinkable(shrunken, english, shrinkingSequence)) {
            shrinkingSequence.add(word);
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
            cout << "It's shrinkable! Here we go: " << endl;
            for (string word: shrinkingSequence) {
                cout << word << endl;
            }
            cout << endl;
        } else {
            cout << "Alas, such shrinking may not be done." << endl;
        }
    }
}
