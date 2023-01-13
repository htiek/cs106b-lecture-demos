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

int main() {
    while (true) {
        int val = getInteger("For this trick, I need a number! ");
        cout << "Its digit sum is " << sumOfDigitsOf(n) << endl;
    }
}

/* Given a number n, returns the sum of the digits of n. */
int sumOfDigitsOf(int n) {
    /* Base case: The sum of all the digits of a number
     * with just one digit is that digit itself.
     */
    if (n < 10) {
        return n;
    }
    /* Recursive step: Peel off the last digit. */
    else {
        return sumOfDigitsOf(n / 10) + (n % 10);
    }
}

