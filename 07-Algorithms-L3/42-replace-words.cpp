#include <string>
#include <iostream>



std::string replaceAll(std::string str, std::string wordToReplace, std::string newWord) {

	short pos = str.find(wordToReplace);
	while ( pos != std::string::npos) {
		str = str.replace(pos, wordToReplace.length(), newWord);
		pos = str.find(wordToReplace);
	}
	return str;
}


int main() {

	std::string str = "Welcome to Jordan , Jordan is a nice country";
	std::string wordToReplace = "Jordan";
	std::string newWord = "USA";
	
	std::string newStr = replaceAll(str, wordToReplace, newWord);

	std::cout << "\nOriginal String is: " << str << std::endl;
	std::cout << "\nWord to Replace is: " << wordToReplace << std::endl;
	std::cout << "\nNew Word is: " << newWord << std::endl;
	std::cout << "\nReplaced String is: " << newStr << std::endl;

}