/* File: ShrinkableWords.cpp
 *
 * Code to find all the shrinkable words in English!
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "console.h"
using namespace std;

bool isShrinkableWord(const string& word, const Lexicon& english) {
    /* Base Case 1: Things must be words to be shrinkable words. */
    if (!english.contains(word)) {
        return false;
    }
    /* Base Case 2: If you're a single letter, then yes, you're shrinkable. */
    if (word.length() == 1) {
        return true;
    }

    /* Recursive Case: Try removing each letter. */
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

    for (string word: english) {
        if (word.length() >= 9 && isShrinkableWord(word, english)) {
            cout << word << endl;
        }
    }

    return 0;
}
