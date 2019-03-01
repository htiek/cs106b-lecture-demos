/*****************************************************
 * File: Main.cpp
 *
 * A program to play around with our new hash set!
 */
#include <iostream>
#include "OurHashSet.h"
#include "console.h"
#include "simpio.h"
using namespace std;

int main() {
    OurHashSet set;
    set.add("Calliope");
    set.add("Polyhymnia");
    set.add("Euterpe");
    set.add("Terpsichore");
    set.add("Urania");
    set.add("Clio");
    set.add("Erato");
    set.add("Melpomene");
    set.add("Thalia");

    while (true) {
        string name = getLine("What are you musing about? ");
        if (set.contains(name)) {
            cout << "Muse-ic to my ears!" << endl;
        } else {
            cout << "We are not a-mused." << endl;
        }
    }

    return 0;
}
