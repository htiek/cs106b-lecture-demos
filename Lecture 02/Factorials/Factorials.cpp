/* File: Factorials.cpp
 *
 * A program that computes n!.
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int factorial(int n);

int main() {
    int n = getInteger("Enter an integer: ");
    cout << n << "! = " << factorial(n) << endl;
    return 0;
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
