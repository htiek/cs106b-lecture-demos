/* File: PredictionTheFirst.cpp
 *
 * What will this program print?
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
using namespace std;

/* By itself, this has no effect. Change the
 * parameter to a reference parameter to make
 * the magic happen.
 */
void becomeWealthy(int& netWorth) {
    netWorth = 1000000000;
}

int main() {
    int netWorth = 137;
    becomeWealthy(netWorth);
    cout << netWorth << endl; // <-- Here
    return 0;
}





