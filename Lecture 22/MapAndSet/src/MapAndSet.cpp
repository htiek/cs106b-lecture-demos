#include "map.h"
#include "set.h"
#include "hashmap.h"
#include "hashset.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/**
 * Given a word, returns whether that word is a tautonym, a word
 * that consists of the same string repeated twice.
 *
 * @param word The word to check.
 * @return Whether it's a tautonym.
 */
bool isTautonym(const string& word) {
    /* If the word length isn't even, it can't be a tautonym. */
    if (word.length() % 2 != 0) {
        return false;
    }

    /* Check if the first and second halves of the word are equal. */
    int half = word.length() / 2;
    return word.substr(0, half) == word.substr(half);
}

int main() {
    /* Build a map from letters to all the words that start with that letter. */
    HashMap<char, HashSet<string>> wordsByFirstLetter;
    ifstream input("EnglishWords.txt");
    for (string word; getline(input, word); ) {
        wordsByFirstLetter[word[0]].add(word);
    }

    /* Have some fun! */
    while (true) {
        string input = getLine("Enter a letter: ");
        if (input.length() == 1 && isalpha(input[0])) {
            for (string word: wordsByFirstLetter[toLowerCase(input[0])]) {
                if (isTautonym(word)) {
                    cout << word << endl;
                }
            }
        }
    }
}
