/* File: DigitalDigits.cpp
 *
 * A program that explores properties of digits of
 * numbers!
 */
#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int sumOfDigitsOf(int n);
int digitalRootOf(int n);

int main() {
    while (true) {
        int val = getInteger("For this trick, I need a number! ");
        cout << "Its digital root is " << digitalRootOf(val) << endl << endl;
    }
}

/* Given a number n, returns the sum of the digits of n. */
int sumOfDigitsOf(int n) {
    if (n < 10) {
        return n;
    } else {
        return sumOfDigitsOf(n / 10) + (n % 10);
    }
}

/* Given a number n, returns the digital root of n. */
int digitalRootOf(int n) {
    /* Keep summing the digits of n until we get down to a single digit. */
    while (n >= 10) {
        n = sumOfDigitsOf(n);
    }
    return n;
}
