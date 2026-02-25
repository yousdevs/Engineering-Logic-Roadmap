#include <string>
#include <iostream>

std::string readString()
{
	std::string str;
	std::cout << "\nPlease Enter Your String?\n";
	std::getline(std::cin, str);
	return str;
}
char readChar()
{
	char letter;
	std::cout << "\nPlease Enter a Character?\n";
	std::cin >> letter;
	return letter;
}
char invertLetterCase(char l)
{
	return isupper(l) ? tolower(l) : toupper(l);
}
short countLetter(std::string str, char letter, bool matchCase = true)
{
	short counter = 0;
	for (short i = 0; i < str.length(); i++)
	{
		if (matchCase)
		{
			if (str[i] == letter)
				counter++;
		}
		else
		{
			if (tolower(str[i]) == tolower(letter))
				counter++;
		}
	}
	return counter;
}

int main()
{
	std::string str = readString();
	char letter = readChar();
	std::cout << "\nLetter \'" << letter << "\' Count = " <<
		countLetter(str, letter);
	std::cout << "\nLetter \'" << letter << "\' ";
	std::cout << "Or \'" << invertLetterCase(letter) << "\' ";
	std::cout << " Count = " << countLetter(str, letter, false);
}