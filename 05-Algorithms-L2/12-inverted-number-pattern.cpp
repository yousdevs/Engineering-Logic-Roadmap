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
	
	for (int i = number; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

}

int main() {
	printInvertedNumberPattern(readPositiveNumber("Please enter a positive number: "));
	return 0;
}