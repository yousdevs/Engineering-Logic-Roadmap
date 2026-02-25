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


void printCounts(std::string str) {
	int length = str.length();
	printf("\nString Length is: %d", length);
	int upperLetters = 0, smallLetters = 0;
	for (int i = 0; i < length; i++) {
		if (std::isupper(str[i]) && str[i] != ' ') {
			upperLetters++;
		}
		else {
			smallLetters++;
		}
	}
	printf("\nUppers: %d \nLowers: %d", upperLetters, smallLetters);
}

int main() {

	std::string str = "MUHAMMED abu hadhud";

	printCounts(str);


	return 0;
}