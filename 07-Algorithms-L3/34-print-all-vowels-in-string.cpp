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

void printAllVowelsIn(std::string str) {
	printf("\n");
	for (short i = 0; i < str.length(); i++) {
		if(isVowel(str[i])) printf(" %c ", str[i]);
	}
}

int main() {

	std::string str = readString();
	printAllVowelsIn(str);


	


	return 0;
}