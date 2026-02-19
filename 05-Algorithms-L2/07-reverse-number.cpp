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

int reverseNumber(int number) {
	// The idea is to take the last digit of the number and add it to the reversed number,
	// then remove the last digit from the original number.
	int reversed = 0;
	while (number > 0) {
		reversed *= 10;
		reversed += number % 10;
		number /= 10;
	}
	return reversed;
}
void printReverseNumber(int number) {
	std::cout << "The reverse of the number is: " << reverseNumber(number) << std::endl;
}

int main() {
	printReverseNumber(readPositiveNumber("Please enter a positive number: "));
	return 0;
}