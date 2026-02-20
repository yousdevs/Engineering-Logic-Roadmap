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

int myCeil(float number) {
	float fraction = getFraction(number);
	if (abs(fraction) > 0) {
		if (number > 0) {
			return (int)number + 1;
		}
		else {
			return (int)number;
		}
	}
	else {
		return number;
	}
	
}

void printResult(float number) {
	std::cout << "My Ceil Result: " << myCeil(number) << std::endl;
	std::cout << "C++ Ceil Result: " << ceil(number) << std::endl;
}

int main() {
	printResult(readNumber("Enter a number: "));
	return 0;
}