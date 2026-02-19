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

void printInvertedNumberPattern(int number) {
	int base = 64;
	for (int i = 0 + base; i <= number + base; i++) {
		for (int j = 0 + base; j < i; j++) {
			std::cout << char(i) << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	printInvertedNumberPattern(readPositiveNumber("Please enter a positive number: "));
	return 0;
}