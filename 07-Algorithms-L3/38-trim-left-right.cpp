#include <iostream>
#include <string>


std::string trimLeft(std::string str) {

	for (short i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			return str.substr(i, str.length() - 1);
		}
	}
	return "";
}

std::string trimRight(std::string str) {

	for (short i = str.length() - 1; i >= 0; i--) {
		if (str[i] != ' ') {
			return str.substr(0, i+1);
		}
	}
	return "";
}

std::string trim(std::string str) {
	return trimLeft(trimRight(str));
}

int main() {

	std::cout << "\nLeft: " << trimLeft("        Ahmed");

	std::cout << "\nRight: " << trimRight("        Ahmed           ") << "A";

	std::cout << "\nTrim: " << trim("        Ahmed           ") << "A";

	return 0;
}