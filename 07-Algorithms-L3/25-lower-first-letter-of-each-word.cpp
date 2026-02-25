#include <iostream>
#include <string>

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

std::string lowerFirstLetterOfEachWord(std::string str) {
	int len = str.length();

	bool isNewWord = true;
	for (short i = 0; i < len; i++) {
		if (isNewWord && str[i] != ' ') {
			str[i] = std::tolower(str[i]);
		}
		if (str[i] == ' ') {
			isNewWord = true;
		}
		else {
			isNewWord = false;
		}

	}
	return str;
}

int main() {

	std::string str = readString();
	std::string newStr = lowerFirstLetterOfEachWord(str);
	std::cout << newStr << std::endl;
	return 0;
}