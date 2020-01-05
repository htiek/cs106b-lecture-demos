def sumOfDivisorsOf(n):
	"""Returns the sum of the positive divisors of the number n >= 0."""
	total = 0
	
	for i in range(1, n):
		if n % i == 0:
			total += i
	
	return total

found = 0   # How many perfect numbers we've found
number = 1	# Next number to test	

# Keep looking until we've found four perfect numbers.	
while found < 4:
	# A number is perfect if the sum of its divisors is equal to it.
	if sumOfDivisorsOf(number) == number:
		print(number)
		found += 1

	number += 1
