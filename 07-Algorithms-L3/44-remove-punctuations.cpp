#include <iostream>
#include <string>


std::string removePunctuationsFromString(std::string str)
{
	std::string newStr = "";
	for (short i = 0; i < str.length(); i++)
	{
		if (!ispunct(str[i]))
		{
			newStr += str[i];
		}
	}
	return newStr;
}

int main()
{
	std::string str = "Hello, World! Welcome to C++ programming.";
	std::string newStr = removePunctuationsFromString(str);
	std::cout << "\nOriginal String: " << str << std::endl;
	std::cout << "\nString without Punctuations: " << newStr << std::endl;
	return 0;
}