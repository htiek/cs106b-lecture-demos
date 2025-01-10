/* File: DigitalDigits.cpp
 *
 * A program that explores properties of digits of
 * numbers!
 */
#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given a nonnegative integer n, returns the sum of the
 * digits of the number n.
 */
int sumOfDigitsOf(int n);

int main() {
    /* Prompt the user for a number and print its digit sum. */
    int n = getInteger("Enter an integer: ");
    int digitSum = sumOfDigitsOf(n);
    cout << n << " sums to " << digitSum << endl;

    return 0;
}

