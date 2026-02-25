#include <iostream>
#include <string>
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
int main() {

	std::vector<std::string> v = split("Programming advices", " ");
	for (std::string &word : v) {
		std::cout << word << std::endl;
	}


	return 0;
}