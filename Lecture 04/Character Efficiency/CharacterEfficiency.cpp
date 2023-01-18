/* File: CharacterEfficiency.cpp
 *
 * A program for finding the English word with the highest ratio
 * of length to number of distinct letters.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "set.h"
using namespace std;


/* Returns the letter efficiency of the word: the ratio of its length
 * to the number of distinct characters it contains.
 */
double efficiencyOf(const string& word) {
    /* Use a set because it doesn't allow for duplicates. */
    Set<char> letters;
    for (char ch: word) {
        letters += ch;
    }

    /* Cast to double so we don't divide and round down. */
    return double(word.length()) / letters.size();
}

int main() {
    Lexicon english("EnglishWords.txt");

    /* Best we've seen so far. */
    double bestEfficiency = 0;
    string bestWord;

    /* Try all words and take the best. */
    for (string word: english) {
        double efficiency = efficiencyOf(word);

        /* If this is more efficient than the most efficient word
         * we've seen so far, update what we think is the best.
         */
        if (efficiency > bestEfficiency) {
            bestEfficiency = efficiency;
            bestWord = word;
        }
    }

    cout << "The most efficient word is... " << bestWord << "!" << endl;
    cout << "Its efficiency is " << bestEfficiency << "." << endl;
    cout << "Now you know!" << endl;

    return 0;
}




























