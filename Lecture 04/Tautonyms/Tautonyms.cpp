/* File: Tautonyms.cpp
 *
 * A program that finds all tautonyms in the English language.
 * (A tautonym is a string that consists of the same string
 * repeated twice.)
 */
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
using namespace std;


/* Given a string, returns whether it's a tautonym. */
bool isTautonym(const string& word) {
    /* This is a different but equivalent implementation to the one we saw
     * in lecture.
     */
    return word.length() % 2 == 0 &&
           word.substr(0, word.length() / 2) == word.substr(word.length() / 2);
}

int main() {
    Lexicon english("EnglishWords.txt");

    /* Scan over all words and print the tautonyms. */
    for (string word: english) {
        if (isTautonym(word)) {
            cout << word << endl;
        }
    }

    return 0;
}




























