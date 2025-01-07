def isPrime(n):
    """Returns whether the input number is prime; assumes n >= 2."""
    # Try dividing by all numbers from 2 to n - 1, inclusive.
    for divisor in range(2, n):
        if n % divisor == 0:
            return False

    return True


found = 0   # How many prime numbers we've found
number = 1  # Next number to test    

# Keep trying numbers until we've found 5000 primes.
while found < 5000:
    number += 1
    
    if isPrime(number):
        found += 1
 
# Last number tried is the 5000th prime.
print(number)
