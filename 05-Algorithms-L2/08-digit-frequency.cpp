#include <iostream>


int readPositiveNumber(std::string message) {
	int number = 0;
	do
	{
		std::cout << message << std::endl;
		std::cin >> number;
	} while (number <= 0);
	return number;
}

int countDigitFrequency(int number, int digit) {
	// The idea is to take the last digit of the number and compare it with the given digit,
	// then remove the last digit from the original number.
	int count = 0;

	while (number > 0) {
		if (number % 10 == digit) {
			count++;
		}
		number /= 10;
	}

	return count;
}

int main() {
	int number = readPositiveNumber("Please enter a positive number: ");
	int digit = readPositiveNumber("Please enter a digit to count: ");
	std::cout << "The frequency of the digit " << digit << " in the number " << number << " is: " << countDigitFrequency(number, digit) << std::endl;
	return 0;
}