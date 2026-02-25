#include <iostream>
#include <string>

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
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

short countVowels(std::string str) {
	short count = 0;
	for (short i = 0; i < str.length(); i++) {
		if (isVowel(str[i])) count++;
	}
	return count;
}
int main() {

	std::string str = readString();
	short count = countVowels(str);
	

	printf("\nCount of Vowels is: %d", count);
	

	return 0;
}