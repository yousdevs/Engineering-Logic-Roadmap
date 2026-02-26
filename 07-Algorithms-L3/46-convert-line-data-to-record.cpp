#include <iostream>
#include <string>
#include <vector>


std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

struct Account {
	std::string accountNumber = "";
	std::string pinCode = "";
	std::string fullName = "";
	std::string phoneNumber = "";
	std::string balance = "";
};
Account readDataFromUser() {
	Account account = {};
	std::cout << "\nPlease Enter Account Number: ";
	account.accountNumber = readString();
	std::cout << "\nPlease Enter Pin Code: ";
	account.pinCode = readString();
	std::cout << "\nPlease Enter Full Name: ";
	account.fullName = readString();
	std::cout << "\nPlease Enter Phone Number: ";
	account.phoneNumber = readString();
	std::cout << "\nPlease Enter Balance: ";
	account.balance = readString();
	return account;
}

std::vector<std::string> convertRecordToVector(Account account) {
	std::vector<std::string> v{};
	v.push_back(account.accountNumber);
	v.push_back(account.pinCode);
	v.push_back(account.fullName);
	v.push_back(account.phoneNumber);
	v.push_back(account.balance);
	return v;
}

std::string joinString(std::vector <std::string> v, std::string delim) {
	std::string str = "";
	for (std::string& s : v) {
		str += s;
		str += delim;
	}
	return str.substr(0, str.length() - delim.length());
}



std::string convertRecordForSaving(Account account) {

	return joinString(convertRecordToVector(account), "#//#");

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

Account convertLineToRecord(std::string line, std::string seperator) {
	std::vector<std::string> v = split(line, seperator);
	Account account = {};
	account.accountNumber = v[0];
	account.pinCode = v[1];
	account.fullName = v[2];
	account.phoneNumber = v[3];
	account.balance = v[4];
	return account;
}

int main() {

	std::cout << "\nPlease Enter Account Data: \n";
	Account account = readDataFromUser();
	std::string record = convertRecordForSaving(account);
	std::cout << "\nRecord for Saving is: " << record << std::endl;

	Account account2 = convertLineToRecord(record, "#//#");
	std::cout << "\nAccount Number: " << account2.accountNumber << std::endl;
	std::cout << "\nPin Code: " << account2.pinCode << std::endl;
	std::cout << "\nFull Name: " << account2.fullName << std::endl;
	std::cout << "\nPhone Number: " << account2.phoneNumber << std::endl;
	std::cout << "\nBalance: " << account2.balance << std::endl;

	return 0;
}