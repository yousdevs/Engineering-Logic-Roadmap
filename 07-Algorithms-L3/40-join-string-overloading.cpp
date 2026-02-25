#include <iostream>
#include <string>
#include <vector>


std::string joinString(std::vector <std::string> v, std::string delim) {
	std::string str = "";
	for (std::string& s : v) {
		str += s;
		str += delim;
	}
	return str.substr(0, str.length() - delim.length());
}

std::string joinString(std::string arr[], short length, std::string delim) {
	std::string str = "";
	for (short i = 0; i < length; i++) {
		str += arr[i];
		str += delim;
	}
	return str.substr(0, str.length() - delim.length());
}

int main() {
	std::vector <std::string> v{};
	v.push_back("Ahmed");
	v.push_back("Khaled");
	v.push_back("Omar");

	std::cout << joinString(v, "#_#") << std::endl;

	std::string arr[] = { "Ahmed", "Omar", "Karam" };
	std::cout << joinString(arr, 3, "<");

	return 0;
}