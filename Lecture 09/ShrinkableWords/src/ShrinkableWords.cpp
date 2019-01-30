/* File: ShrinkableWords.cpp
 *
 * Code to find all the shrinkable words in English!
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "console.h"
using namespace std;

bool isShrinkable(const string& word, const Lexicon& english) {
    if (!english.contains(word)) return false;
    if (word.length() == 1) return true;

    for (int i = 0; i < word.length(); i++) {
        string shrunken = word.substr(0, i) + word.substr(i + 1);
        if (isShrinkable(shrunken, english)) return true;
    }

    return false;
}

int main() {
    Lexicon english("EnglishWords.txt");

    for (string word: english) {
        if (word.length() >= 9 && isShrinkable(word, english)) {
            cout << word << endl;
        }
    }

    return 0;
}
