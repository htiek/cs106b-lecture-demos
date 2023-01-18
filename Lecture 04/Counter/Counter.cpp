/* File: Counter.cpp
 *
 * A program that remembers how many times each phrase has
 * been seen.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "map.h"
using namespace std;

int main() {
    /* Frequency map: each string is associated with its frequency. */
    Map<string, int> freqMap;
    while (true) {
        string text = getLine("Enter some text: ");

        /* If freqMap[text] doesn't yet exist, it's created and set
         * it to zero.
         */
        cout << "Times seen: " << freqMap[text] << endl;
        freqMap[text]++;
    }
}




























