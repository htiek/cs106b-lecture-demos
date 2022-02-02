/* File: PredictionTheSecond.cpp
 *
 * What will this program print?
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
using namespace std;

void gollyGee(const string& text) {
    text[0] = 'g';
}

int main() {
    string message = "wiggle";
    gollyGee(message);
    cout << message << endl; // <-- Here
    return 0;
}





