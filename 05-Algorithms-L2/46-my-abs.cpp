#include <iostream>

float readNumber(std::string message) {
	float number = 0;
	
	std::cout << message << std::endl;
	std::cin >> number;
	
	return number;
}

float myAbs(float number) {
	if (number < 0)
		return number * -1;
	return number;
}

void printResult(float number) {
	std::cout << "My Abs Result: " << myAbs(number) << std::endl;
	std::cout << "C++ Abs Result: " << abs(number) << std::endl;
}

int main() {
	printResult(readNumber("Enter a number: "));
	return 0;
}