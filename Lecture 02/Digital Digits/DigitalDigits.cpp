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
        cout << "Its digit sum is " << sumOfDigitsOf(val) << "." << endl << endl;
    }
}


int sumOfDigitsOf(int n) {
    /* Base Case: Any one-digit number sums to itself. */
    if (n < 10) {
        return n;
    }
    /* Recursive Case: To add up the digits of a multi-
     * digit number, add up all but the last digit, then
     * add in the last digit.
     */
    else {
        return sumOfDigitsOf(n / 10) + (n % 10);
    }
}







