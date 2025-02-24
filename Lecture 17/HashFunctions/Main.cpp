/*****************************************************
 * File: Main.cpp
 *
 * A program to play around with hash functions!
 */
#include <iostream>
#include "HashFunction.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

int main() {
    /* All cities in Santa Clara County. */
    Vector<string> cities = {
        "Campbell",        // Check out the famous water tower
        "Cupertino",       // Home of Apple, Inc.
        "Gilroy",          // Of the famous garlic festival
        "Los Altos",       // Not to be confused with Los Altos Hills
        "Los Altos Hills", // Not to be confused with Los Altos
        "Los Gatos",       // Home of Netflix
        "Milpitas",        // Visit Ed R. Levin County Park
        "Monte Sereno",    // Where "The Grapes of Wrath" was written
        "Morgan Hill",     // Visit Henry Coe State Park
        "Mountain View",   // Home of Alphabet, Inc.
        "Palo Alto",       // Huh, I've never heard of it
        "San José",        // 10th largest city in the US
        "Santa Clara",     // Home of Levi's Stadium
        "Saratoga",        // See a concert at Mountain Winery
        "Sunnyvale"        // Former fruitpacking capital
    };

    /* Get a hash function that outputs an index into this list. */
    HashFunction<string> hashFn = forSize(cities.size());

    while (true) {
        string name = getLine("Enter your name: ");
        int hashCode = hashFn(name); // Assign cities by hash code
        cout << "You need to canvas in " << cities[hashCode] << "." << endl;
    }
}
