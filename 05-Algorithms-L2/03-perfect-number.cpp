#include <iostream>

bool isDivisor(int number, int divisor) {
	return (number % divisor == 0);
}

int sumOfDivisors(int number) {
	int sum = 0;
	for (int i = 1; i < number; i++) {
		if (isDivisor(number, i)) {
			sum += i;
		}
	}
	return sum;
}

enum enNumberType { Perfect = 1, NotPerfect = 0 };

enNumberType checkPerfect(int number) {
	int sum = sumOfDivisors(number);
	if (sum == number) {
		return enNumberType::Perfect;
	}
	return enNumberType::NotPerfect;
}

int readPositiveNumber(std::string message) {
	int number = 0;
	do
	{
		std::cout << message << std::endl;
		std::cin >> number;
	} while (number <= 0);
	return number;
}

void printCheckPerfect(int number) {
	if (checkPerfect(number) == enNumberType::Perfect) {
		std::cout << number << " is a perfect number." << std::endl;
	}
	else {
		std::cout << number << " is not a perfect number." << std::endl;
	}
}

int main() {
	printCheckPerfect(readPositiveNumber("Please enter a positive number: "));
}