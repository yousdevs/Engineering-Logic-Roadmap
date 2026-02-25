#include <iostream>


char readChar()
{
	char letter;
	std::cout << "\nPlease Enter a Character?\n";
	std::cin >> letter;
	return letter;
}

enum enVowelChars {
	A = 'a',
	E = 'e',
	I = 'i',
	O = 'o',
	U = 'u',
};
bool isVowel(char c) {
	return (std::tolower(c) == enVowelChars::A ||
		c == enVowelChars::E ||
		c == enVowelChars::I ||
		c == enVowelChars::O ||
		c == enVowelChars::U);
}

int main() {

	char c = readChar();
	if (isVowel(c)) {
		printf("\nYes, letter %c is vowel");
	}
	else {
		printf("\nNo, letter %c is not vowel");
	}

	return 0;
}