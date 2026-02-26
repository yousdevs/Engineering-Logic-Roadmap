#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct stClient {
	std::string accountNumber = "";
	std::string pinCode = "";
	std::string fullName = "";
	std::string phoneNumber = "";
	double balance = 0.0;
};

std::vector<std::string> convertRecordToVector(stClient client) {
	std::vector<std::string> v{};
	v.push_back(client.accountNumber);
	v.push_back(client.pinCode);
	v.push_back(client.fullName);
	v.push_back(client.phoneNumber);
	v.push_back(std::to_string(client.balance));
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

std::string convertRecordForSaving(stClient client) {
	return joinString(convertRecordToVector(client), "#//#");
}

void saveRecordToFile(stClient client, std::string fileName) {
	std::string record = convertRecordForSaving(client);
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::app);
	if(file.is_open()) {
		file << record << std::endl;
		file.close();
	}
	else {
		std::cout << "\nError: Can't open file\n";
	}
}

void saveRecords(std::vector<stClient> clients, std::string fileName) {
	
	for (stClient& client : clients) {
		saveRecordToFile(client, fileName);
	}
}

std::string readString() {
	std::string str = "";
	std::getline(std::cin, str);
	return str;
}

std::vector<stClient> readClients(){
	char choice = 'y';
	std::string input = "";

	
	std::vector<stClient> clients{};
	do {
		stClient client = {};
		std::cout << "\nAdding new client: \n";
		std::cout << "\nPlease Enter Account Number: ";
		client.accountNumber = readString();
		std::cout << "\nPlease Enter Pin Code: ";
		client.pinCode = readString();
		std::cout << "\nPlease Enter Full Name: ";
		client.fullName = readString();
		std::cout << "\nPlease Enter Phone Number: ";
		client.phoneNumber = readString();
		std::cout << "\nPlease Enter Balance: ";
		client.balance = std::stod(readString());
		clients.push_back(client);

		std::cout << "\nDo you want to add another client? (y/n): ";
		std::getline(std::cin, input);

		if (!input.empty())
			choice = input[0];
	} while (choice == 'y' || choice == 'Y');
	return clients;
}

int main() {
	
	std::vector<stClient> clients = readClients();
	std::string fileName = "clients.txt";

	saveRecords(clients, fileName);
	std::cout << "\nClients have been saved to file: " << fileName << std::endl;
	
	return 0;

}