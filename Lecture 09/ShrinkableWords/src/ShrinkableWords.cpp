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
    /* Base case: Not a word? Then it's not a shrinkable word! */
    if (!english.contains(word)) {
        return false;
    }
    /* Base case: Is a single letter long! Then it's shrinkable! */
    if (word.length() == 1) {
        return true;
    }
    /* Recursive step: Try removing each character and see if any of them work. */
    for (int i = 0; i < word.length(); i++) {
        string remaining = word.substr(0, i) + word.substr(i + 1);
        if (isShrinkableWord(remaining, english)) {
            return true;
        }
    }

    /* None of those options worked? Definitely not shrinkable. */
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
