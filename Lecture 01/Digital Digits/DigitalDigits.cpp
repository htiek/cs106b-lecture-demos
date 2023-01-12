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
    int n = getInteger("Enter an integer: ");
    int digitSum = sumOfDigitsOf(n);
    cout << n << " sums to " << digitSum << endl;

    return 0;
}

/* Given an integer n, returns the sum of the digits of the
 * number n.
 */
int sumOfDigitsOf(int n) {
    /* Sum of the digits we've seen thus far. */
    int result = 0;

    while (n > 0) {
        /* Add the last digit of n. */
        result += (n % 10);

        /* Drop off the last digit of n. */
        n /= 10;
    }
    return result;
}






