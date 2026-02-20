#include <iostream>

float readNumber(std::string message) {
	float number = 0;

	std::cout << message << std::endl;
	std::cin >> number;

	return number;
}

float getFraction(float number) {
	return number - int(number);
}

int mySqrt(float number) {
	return pow(number, 0.5);
}

void printResult(float number) {
	std::cout << "My Sqrt Result: " << mySqrt(number) << std::endl;
	std::cout << "C++ Sqrt Result: " << sqrt(number) << std::endl;
}

int main() {
	printResult(readNumber("Enter a number: "));
	return 0;
}