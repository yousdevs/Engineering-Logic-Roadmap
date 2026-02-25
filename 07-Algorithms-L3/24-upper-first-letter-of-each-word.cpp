#include <iostream>
#include <string>

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

void upperFirstLetterOfEachWord(std::string &str) {
	int len = str.length();

	bool isNewWord = true;
	for (short i = 0; i < len; i++) {
		if (isNewWord && str[i] != ' ') {
			str[i] = std::toupper(str[i]);
		}
		if (str[i] == ' ') {
			isNewWord = true;
		}
		else {
			isNewWord = false;
		}

	}
}

int main() {

	std::string str = readString();
	upperFirstLetterOfEachWord(str);
	std::cout << str << std::endl;
	return 0;
}