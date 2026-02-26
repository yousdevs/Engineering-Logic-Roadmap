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

 std::string convertRecordForSaveing(Account account) {
 
	 return joinString(convertRecordToVector(account), "#//#");

 }

int main() {
	
	std::cout << "\nPlease Enter Account Data: \n";
	Account account = readDataFromUser();
	std::string record = convertRecordForSaveing(account);
	std::cout << "\nRecord for Saving is: " << record << std::endl;
	return 0;
}