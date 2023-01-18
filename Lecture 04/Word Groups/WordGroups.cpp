/* File: WordGroups.cpp
 *
 * A program that clusters words into groups based on their
 * first letter.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
#include "map.h"
#include "set.h"
using namespace std;

int main() {
    Lexicon english("EnglishWords.txt");

    /* First character to all words starting with that character.
     * We use the magic of autoinsertion here: if word[0] isn't
     * already a key here, then wordsByFirstLetter will create
     * a new empty Lexicon associated with that letter.
     */
    Map<char, Lexicon> wordsByFirstLetter;
    for (string word: english) {
        wordsByFirstLetter[word[0]] += word;
    }

    /* Sit in a loop and ask the user for a letter. */
    while (true) {
        char ch = getChar("Enter a letter: ");
        if (wordsByFirstLetter.containsKey(ch)) {
            cout << wordsByFirstLetter[ch] << endl;
        } else {
            cout << ">:-(" << endl;
        }
    }
}




























