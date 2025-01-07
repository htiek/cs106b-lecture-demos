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



