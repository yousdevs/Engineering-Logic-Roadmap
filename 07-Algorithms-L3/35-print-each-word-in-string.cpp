#include <iostream>
#include <string>


std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

void printWord(std::string str, short startIndex, short endIndex) {
	std::string word = "";
	for (short i = startIndex; i <= endIndex; i++) {
		word += str[i];
	}
	std::cout << word << std::endl;
}

void printEachWordInString(std::string str) {

	short wordStartPos = 0;
	short wordEndPos = 0;
	for (short i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			printWord(str, wordStartPos, i - 1);
			wordStartPos = i + 1;
		}
		if (i == str.length() - 1) {
			printWord(str, wordStartPos, i );
		}
	}
}

void PrintEachWordInString(std::string S1)
{
	std::string delim = " "; // delimiter
	std::cout << "\nYour string wrords are: \n\n";
	short pos = 0;
	std::string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			std::cout << sWord << std::endl;
		}
		S1.erase(0, pos + delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		std::cout << S1 << std::endl; // it print last word of the string.
	}
}

int main() {
	printEachWordInString(readString());
	return 0;
}