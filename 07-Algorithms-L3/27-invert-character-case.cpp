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

int main() {

	std::cout << invertCharacter('a') << std::endl;
	std::cout << invertCharacter('A') << std::endl;

	return 0;
}