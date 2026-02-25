#include <iostream>
#include <string>

char invertCharacter(char c) {
	if (std::isupper(c)) {
		return std::tolower(c);
	}
	else {
		return std::toupper(c);
	}
}

std::string invertAllLetters(std::string str) {
	short len = str.length();
	for (short i = 0; i < len; i++) {
		str[i] = invertCharacter(str[i]);
	}
	return str;
}

int main() {

	std::string str = "MUHAMMED abu hadhud";
	std::string inverted = invertAllLetters(str);
	std::cout << inverted << std::endl;


	return 0;
}