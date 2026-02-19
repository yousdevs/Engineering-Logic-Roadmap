#include <iostream>

enum enNumberType{ Palindrome = 1, NotPalindrome = 0 };

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
	int reversed = 0;
	while (number > 0) {
		reversed *= 10;
		reversed += number % 10;
		number /= 10;
	}
	return reversed;
}
enNumberType checkPalindrome(int number) {
	if (number == reverseNumber(number)) {
		return enNumberType::Palindrome;
	}
	return enNumberType::NotPalindrome;
}

void printCheckPalindrome(int number) {
	if (checkPalindrome(number) == enNumberType::Palindrome) {
		std::cout << number << " is a palindrome number." << std::endl;
	}
	else {
		std::cout << number << " is not a palindrome number." << std::endl;
	}
}
int main() {
	printCheckPalindrome(readPositiveNumber("Please enter a positive number: "));
	return 0;
}