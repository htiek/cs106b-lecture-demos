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




























