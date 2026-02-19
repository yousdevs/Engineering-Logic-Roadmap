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

void printAllDigitFrequencies(int number) {
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		short digitFrequency = 0;
		digitFrequency = countDigitFrequency(number, i);

		if (digitFrequency > 0)
		{
			std::cout << "Digit " << i << " Frequencey is "
				<< digitFrequency << " Time(s).\n";
		}
	}
}


int main() {
	int number = readPositiveNumber("Please enter a positive number: ");
	printAllDigitFrequencies(number);
	return 0;
}