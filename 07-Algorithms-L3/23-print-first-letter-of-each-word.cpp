#include <iostream>
#include <string>

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

void printFirstLetterOfEachWord(std::string str) {
	int len = str.length();
	
	bool isNewWord = true;
	for (short i = 0; i < len; i++) {
		if (isNewWord && str[i] != ' ') {
			std::cout << str[i] << std::endl;
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
	printFirstLetterOfEachWord(str);

	return 0;
}