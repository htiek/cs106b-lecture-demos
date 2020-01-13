/* File: MoonlightVector.cpp
 *
 * Some simple code to play around with vectors and parameter passing.
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
using namespace std;


void growUp(Vector<string> cast) {
    cast += "Paula";
    cast[0] = "Chiron";
}

int main() {
    Vector<string> moonlight = { "Little", "Teresa", "Kevin" };
    
    growUp(moonlight);
   
    for (string person: moonlight) {
        cout << person << endl;
    }
   
    return 0;
}

