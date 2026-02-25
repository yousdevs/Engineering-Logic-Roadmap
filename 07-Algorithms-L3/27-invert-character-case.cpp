#include <iostream>
#include <string>

char invertCharacter(char c) {
	if (std::isupper(c)) {
		return std::toupper(c);
	}
	else {
		return std::tolower(c);
	}
}

int main() {

	std::cout << invertCharacter('a') << std::endl;
	std::cout << invertCharacter('A') << std::endl;

	return 0;
}