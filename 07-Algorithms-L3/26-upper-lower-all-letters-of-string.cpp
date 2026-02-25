#include <iostream>
#include <string>

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

std::string lowerAllLettersOf(std::string str) {
	int len = str.length();

	for (short i = 0; i < len; i++) {
		if (str[i] != ' ') {
			str[i] = std::tolower(str[i]);
		}
	}
	return str;
}

std::string upperAllLettersOf(std::string str) {
	int len = str.length();

	for (short i = 0; i < len; i++) {
		if (str[i] != ' ') {
			str[i] = std::toupper(str[i]);
		}
	}
	return str;
}

int main() {

	std::string str = readString();
	std::string newStr = lowerAllLettersOf(str);
	std::cout << newStr << std::endl;
	std::string uppered = upperAllLettersOf(str);
	std::cout << uppered << std::endl;
	return 0;
}