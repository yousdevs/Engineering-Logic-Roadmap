#include <iostream>

float readNumber(std::string message) {
	float number = 0;

	std::cout << message << std::endl;
	std::cin >> number;

	return number;
}

int myFloor(float number) {
	
	if (number > 0) {
		return (int)number;
	}
	else {
		return (int)number - 1;
	}
}

void printResult(float number) {
	std::cout << "My Floor Result: " << myFloor(number) << std::endl;
	std::cout << "C++ Floor Result: " << floor(number) << std::endl;
}

int main() {
	printResult(readNumber("Enter a number: "));
	return 0;
}