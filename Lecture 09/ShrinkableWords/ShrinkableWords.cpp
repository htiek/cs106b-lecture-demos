/* File: ShrinkableWords.cpp
 *
 * Code to find all the shrinkable words in English!
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "console.h"
using namespace std;

bool isShrinkableWord(const string& word,
                      const Lexicon& english) {

}

int main() {
    Lexicon english("EnglishWords.txt");

    for (string word: english) {
        if (word.length() >= 9 &&
            isShrinkableWord(word, english)) {
            cout << word << endl;
        }
    }

    return 0;
}
