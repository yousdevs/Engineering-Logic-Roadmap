#include <iostream>
#include <string>
#include <vector>


std::string joinString(std::vector <std::string> v, std::string delim) {
	std::string str = "";
	for (std::string& s : v) {
		str += s;
		str += delim;
	}
	return str.substr(0, str.length() - delim.length() );
}

int main() {
	std::vector <std::string> v{};
	v.push_back("Ahmed");
	v.push_back("Khaled");
	v.push_back("Omar");
	
	std::cout << joinString(v, "#_#");

	return 0;
}