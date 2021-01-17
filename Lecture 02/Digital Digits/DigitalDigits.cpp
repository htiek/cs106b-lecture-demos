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
        cout << "Its digit sum is " << sumOfDigitsOf(val) << endl << endl;
    }
}


/* Given a number n, returns the sum of the digits of n. */
int sumOfDigitsOf(int n) {
    int result = 0;
    
    while (n > 0) {
        result += (n % 10);
        n /= 10;
    }
    
    return result;
}

