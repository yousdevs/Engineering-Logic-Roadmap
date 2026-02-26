#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str, std::string delim) {
	std::vector<std::string> v{};
	short pos = 0;
	std::string word = "";
	while ((pos = str.find(delim)) != str.npos) {
		word = str.substr(0, pos);
		if (word != "") v.push_back(word);
		str.erase(0, pos + delim.length());
	}
	if (str != "") v.push_back(str);
	return v;
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

std::string replaceAll(std::string str, std::string wordToReplace, std::string newWord, bool matchCase = true) {
	std::vector<std::string> v = split(str, " ");
	std::string newStr = "";
	for (short i = 0; i < v.size(); i++) {
		if (matchCase && v[i] == wordToReplace) {
			newStr += newWord + " ";
		}
		else if (!matchCase && lowerAllLettersOf(v[i]) == lowerAllLettersOf(wordToReplace)) {
			newStr += newWord + " ";
		}
		else {
			newStr += v[i] + " ";
		}
	}
	newStr.pop_back(); // to remove the last space
	return newStr;
}


int main() {

	std::string str = "Welcome to Jordan , Jordan is a nice country";
	std::string wordToReplace = "jordan";
	std::string newWord = "USA";

	std::string newStr = replaceAll(str, wordToReplace, newWord, true);

	std::cout << "\nOriginal String is: " << str << std::endl;
	std::cout << "\nWord to Replace is: " << wordToReplace << std::endl;
	std::cout << "\nNew Word is: " << newWord << std::endl;
	std::cout << "\nReplaced String is: " << newStr << std::endl;

}