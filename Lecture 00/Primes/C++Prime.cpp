#include <iostream> 
using namespace std;

/* Returns whether the input number is prime; assumes n >= 2. */
bool isPrime(int n) {
    /* Try dividing by all numbers from 2 to n - 1, inclusive. */
    for (int divisor = 2; divisor < n; divisor++) {
        if (n % divisor == 0) {
            return false;
        } 
    } 
 
    return true;
} 

int main() {
    int found = 0;  // How many prime numbers we've found
    int number = 1; // Next number to test    
 
    /* Keep trying numbers until we've found 5000 primes. */
    while (found < 5000) {
        number++; 
 
        if (isPrime(number)) {
            found++;
        } 
    } 
 
    /* Last number tried is the 5000th prime. */
    cout << number << endl; 
    return 0;
} 
