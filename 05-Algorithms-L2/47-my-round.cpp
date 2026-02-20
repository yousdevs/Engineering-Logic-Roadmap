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

int myRound(float number) {
	float fraction = getFraction(number);
	int intPart = (int)number;

	if (abs(fraction) >= 0.5) {
		if (number > 0) {
			return ++intPart;
		}
		else {
			return --intPart;
		}
	}
	return intPart;
}

void printResult(float number) {
	std::cout << "My Round Result: " << myRound(number) << std::endl;
	std::cout << "C++ Round Result: " << round(number) << std::endl;
}

int main() {
	printResult(readNumber("Enter a number: "));
	return 0;
}