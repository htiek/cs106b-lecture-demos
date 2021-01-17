#include <iostream>
using namespace std;

/* Returns the sum of the positive divisors of the number n >= 0. */
int sumOfDivisorsOf(int n) {
    int total = 0;
    
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            total += i;
        }
    }
    
    return total;
}

int main() {
  int found = 0;  // How many perfect numbers we've found
  int number = 1;    // Next number to test    

  /* Keep looking until we've found four perfect numbers.    */
  while (found < 4) {
      /* A number is perfect if the sum of its divisors is equal to it. */
      if (sumOfDivisorsOf(number) == number) {
          cout << number << endl;
          found++;
      }
    
      number++;
  }
  
  return 0;
}
