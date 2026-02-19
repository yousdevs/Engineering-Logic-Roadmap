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

void printInvertedLetterPattern(int number) {

	for (int i = number + 64 ; i > 64; i--) {
		for (int j = 64; j < i; j++) {
			std::cout << char(i) << " ";
		}
		std::cout << std::endl;
	}
}
//for (int i = number; i > 0; i--) {
//	for (int j = 0; j < i; j++) {
//		std::cout << i << " ";
//	}
//	std::cout << std::endl;
//}
int main() {
	std::cout << char(65) << std::endl;
	printInvertedLetterPattern(readPositiveNumber("Please enter a positive number: "));
	return 0;
}