/* File: EatYourWords.cpp
 *
 * A program that clusters words into anagram clusters
 * to let the user find all anagrams of a word, plus
 * a bunch of other nifty little functions!
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
    Map<char, int> letterFreq;
    for (char ch: input) {
        letterFreq[ch]++;
    }

    /* Iterate over the frequency table and build the result
     * string from the information it contains. The Map type
     * has the nice property that keys are iterated over in
     * sorted order, so this visits the letters in sorted
     * order.
     */
    string result;
    for (char ch: letterFreq) {
        for (int i = 0; i < letterFreq[ch]; i++) {
            result += ch;
        }
    }

    return result;
}



bool isTautonym(const string& word) {
    /* Tautonyms all have even length. */
    if (word.length() % 2 != 0) {
        return false;
    }

    /* Is the first half of the word the same as
     * the second half?
     */
    int half = word.length() / 2;

    /*    DE ER
     *    ^^ ^^
     */
    return word.substr(0, half) == word.substr(half);
}

int main() {

    Map<string, int> freqMap;
    while (true) {
        string text = getLine("Enter some text: ");
        freqMap[text]++;
        cout << "Times seen: " << freqMap[text] << endl;
    }




    /*
    Lexicon english("EnglishWords.txt");

    // 'a' -> {'apple', 'appendix', 'apply', 'aeon', 'aether', ...
    // 'b' -> {'ball', 'balloon', 'baluga', ...
    Map<char, Lexicon> wordsByFirstLetter;
    for (string word: english) {
        wordsByFirstLetter[word[0]] += word;
    }

    cout << wordsByFirstLetter['q'] << endl;
    */
    return 0;
}
















