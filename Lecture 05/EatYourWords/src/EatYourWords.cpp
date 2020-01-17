/* File: EatYourWords.cpp
 *
 * A program that clusters words into anagram clusters
 * to let the user find all anagrams of a word, plus
 * a bunch of other nifty little functions!
 */
#include <iostream>
#include <string>
#include <cctype>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
#include "hashmap.h"
#include "hashset.h"
using namespace std;

/**
 * Given a word, returns a string formed by sorting the letters
 * in that word.
 *
 * @param word The input word
 * @return A sorted version of the word
 */
string sortedVersionOf(const string& input) {
    /* This algorithm is an implementation of an algorithm called
     * "Counting Sort." It's described in the slides for Lecture 05.
     * For more information, take CS161!
     */

    /* Build a frequency table of the letters in the word. */
    HashMap<char, int> letterFreq;
    for (char ch: input) {
        letterFreq[ch]++;
    }

    /* Iterate over the frequency table and build the result
     * string from the information it contains.
     */
    string result;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        for (int i = 0; i < letterFreq[ch]; i++) {
            result += ch;
        }
    }

    return result;
}

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
    Lexicon english("EnglishWords.txt");


    return 0;
}









