#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace mylib {
	std::string readString(const std::string& message = "") {
		std::string input;

		if (!message.empty())
			std::cout << message;

		// Skip any leading whitespace/newlines left in the buffer
		std::getline(std::cin >> std::ws, input);

		return input;
	}

	bool isNumber(std::string s) {
		if (s.empty()) return false;

		int start = (s[0] == '-') ? 1 : 0;
		if (start == 1 && s.length() == 1) return false; // Just a "-" is not a number

		for (int i = start; i < s.length(); i++) {
			if (!isdigit(s[i])) return false;
		}
		return true;
	}

	int readValidInteger(std::string msg = "") {
		std::string input = "";
		bool firstInput = true;
		do {
			if (!firstInput) {
				printf("Please enter valid integer\n");
			}
			else {
				firstInput = false;
			}
			input = readString(msg);
		} while (!isNumber(input));
		return std::stoi(input);
	}

	unsigned int readPositiveInteger() {
		int integer = 0;
		do {
			printf("Please Enter Positive Integer: ");
			integer = readValidInteger();
		} while (integer <= 0);
		return integer;
	}

	short readIntegerInRange(short min, short max) {
		short integer = 0;
		bool firstInput = true;
		do {
			if (!firstInput) {
				std::cout << "\nPlease Enter Integer Between " << std::to_string(min) << " and " << std::to_string(max) << " :" << std::endl;
			}
			else {
				firstInput = false;
			}
			integer = readValidInteger();
		} while (integer < min || integer > max);
		return integer;
	}

	std::vector <std::string> split(std::string str, std::string delim = " ") {
		std::vector<std::string> v{};
		short pos = 0;
		std::string word = "";
		while ((pos = str.find(delim)) != str.npos) {
			word = str.substr(0, pos);
			if (word != "") v.push_back(word);
			str.erase(0, pos + delim.length()); //O(n²)
		}
		if (str != "") v.push_back(str);
		return v;
	}
}
