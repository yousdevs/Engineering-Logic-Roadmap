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

void printDigitsInReversedOrder(int number){
	int reminder = 0;
	while (number > 0) {
		reminder = number % 10;
		std::cout << reminder << std::endl;
		number /= 10;
	}
}

int main() {
	printDigitsInReversedOrder(readPositiveNumber("Please enter a positive number: "));
	return 0;
}