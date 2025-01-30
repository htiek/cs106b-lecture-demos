/* File: ShrinkableWords.cpp
 *
 * Code to find all the shrinkable words in English!
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
using namespace std;

Vector<string> isShrinkableWord(const string& word,
                                const Lexicon& english) {
    /* Base case: Something has to be a word to be a
     * shrinkable word.
     */
    if (!english.contains(word)) {
        return false;
    }
    /* Base case: If length is one, we're done. */
    if (word.length() == 1) {
        return true;
    }

    /* Recursive case: Try removing every character, one at a time,
     * to see if any one of them leaves us with a shrinkable word.
     */
    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) + word.substr(i + 1);
        if (isShrinkableWord(shrunken, english)) {
            return true;
        }
    }

    /* Oh fiddlesticks. */
    return false;
}

int main() {
    Lexicon english("EnglishWords.txt");
    while (true) {
        string word = getLine("Enter a word: ");
        if (isShrinkableWord(word, english)) {
            cout << "Yep!" << endl;
        } else {
            cout << "Nah." << endl;
        }
    }
}
