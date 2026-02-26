#include <string>
#include <iostream>
#include <vector>

std::string readString()
{
	std::string str;
	std::cout << "\nPlease Enter Your String?\n";
	std::getline(std::cin, str);
	return str;
}

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

std::string reverse(std::string str) {
	std::string reversed = "";
	std::vector<std::string> v = split(str, " ");

	for (short i = v.size() - 1; i >= 0; i--) {
		reversed += v[i] + " ";
	}
	reversed = reversed.substr(0, reversed.length() - 1); // to remove the last space
	return reversed;
}

std::string reverseUsingIterator(std::string str) {
	std::string reversed = "";
	std::vector<std::string> v = split(str, " ");
	std::vector<std::string>::iterator iter = v.end();
	while (iter != v.begin()) {
		iter--;
		reversed += *iter + " ";
	}
	reversed.pop_back(); // to remove the last space
	return reversed;
}

int main() {

	std::string str = readString();
	std::string reverserd = reverse(str);
	std::string reverserdUsingIter = reverseUsingIterator(str);
	std::cout << "\nReversed String is: " << reverserd << std::endl;
	std::cout << "\nReversed String using Iterator is: " << reverserdUsingIter << std::endl;
	return 0;
}