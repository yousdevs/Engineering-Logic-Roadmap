#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

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
	if (file.is_open()) {
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

std::vector<stClient> readClients() {
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

stClient convertLineToRecord(std::string line, std::string seperator) {
	std::vector<std::string> v = split(line, seperator);
	stClient client = {};
	client.accountNumber = v[0];
	client.pinCode = v[1];
	client.fullName = v[2];
	client.phoneNumber = v[3];
	client.balance = std::stod(v[4]);
	return client;
}

std::vector<stClient> loadClientsFromFile(std::string fileName, std::string delim) {
	std::vector<stClient> clients{};
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {

			if (line.empty())
				continue;

			std::vector<std::string> v = split(line, delim);

			if (v.size() != 5)
				continue;

			stClient client = convertLineToRecord(line, delim);
			clients.push_back(client);
		}
		file.close();
	}
	else {
		std::cout << "\nError: Can't open file\n";
	}
	return clients;
}

void printClients(std::vector<stClient> clients) {

	std::string clientList = "Client List (" + std::to_string(clients.size()) + ") Client(s).\n";
	std::string line = std::string(120, '-') + "\n";

	std::cout << "\n" << std::setw(75) << clientList;
	std::cout << line;

	// Header
	std::cout << "|"
		<< std::left << std::setw(19) << "Account Number"
		<< "|"
		<< std::left << std::setw(19) << "Pin Code"
		<< "|"
		<< std::left << std::setw(29) << "Full Name"
		<< "|"
		<< std::right << std::setw(19) << "Phone Number"
		<< "|"
		<< std::right << std::setw(14) << "Balance"
		<< "|\n";

	std::cout << line;

	// Data
	for (stClient& client : clients) {
		std::cout << "|"
			<< std::left << std::setw(19) << client.accountNumber
			<< "|"
			<< std::left << std::setw(19) << client.pinCode
			<< "|"
			<< std::left << std::setw(29) << client.fullName
			<< "|"
			<< std::right << std::setw(19) << client.phoneNumber
			<< "|"
			<< std::right << std::setw(14) << client.balance
			<< "|\n";
	}

	std::cout << line;
}

struct stFoundClient {
	stClient client;
	bool found = false;
};

stFoundClient searchClientByAccountNumber(std::vector<stClient> clients, std::string accountNumber) {

	stFoundClient foundClient = {
		{}, false
	};
	for (stClient& client : clients) {
		if (client.accountNumber == accountNumber) {

			foundClient.client = client;
			foundClient.found = true;
			return foundClient;
		}
	}
	return foundClient;
}

void printClient(stClient client) {
	//printClients({ foundClient.client });
	std::cout << "\nClient Found: \n";
	std::cout << "Account Number: " << client.accountNumber << std::endl;
	std::cout << "Pin Code: " << client.pinCode << std::endl;
	std::cout << "Full Name: " << client.fullName << std::endl;
	std::cout << "Phone Number: " << client.phoneNumber << std::endl;
	std::cout << "Balance: " << client.balance << std::endl;
}

void saveUpdatedRecords(std::vector<stClient> clients, std::string fileName) {
	std::fstream file;
	file.open(fileName, std::ios::out);
	if (file.is_open()) {
		for (stClient& client : clients) {
			std::string record = convertRecordForSaving(client);
			file << record << std::endl;
		}
		file.close();
	}
	else {
		std::cout << "\nError: Can't open file\n";
	}
}

void deleteClientByAccountNumber(std::vector <stClient> clients, std::string accountNumber, std::string fileName) {
	std::vector<stClient> updatedClients{};
	for (stClient& client : clients) {
		if (client.accountNumber != accountNumber) {
			updatedClients.push_back(client);
		}
	}
	saveUpdatedRecords(updatedClients, fileName);
}

void confirmAndDeleteClient(std::vector<stClient> clients, stClient client, std::string fileName) {
	char choice = 'n';
	std::cout << "\nAre you sure you want to delete this client? (y/n): ";
	std::string input;
	std::getline(std::cin, input);
	choice = input[0];

	if (tolower(choice) == 'y') {
		deleteClientByAccountNumber(clients, client.accountNumber, fileName);
		std::cout << "\nClient with Account Number (" << client.accountNumber << ") has been deleted.\n";
	}
}

stClient readUpdatedClientData(std::string accountNumber) {
	stClient client = {};

	client.accountNumber = accountNumber;
	std::cout << "\nPlease Enter Pin Code: ";
	client.pinCode = readString();
	std::cout << "\nPlease Enter Full Name: ";
	client.fullName = readString();
	std::cout << "\nPlease Enter Phone Number: ";
	client.phoneNumber = readString();
	std::cout << "\nPlease Enter Balance: ";
	client.balance = std::stod(readString());
	return client;
}

std::vector<stClient> updateClients(std::vector <stClient> clients, stClient updatedClient) {
	for (stClient& c : clients) {
		if (c.accountNumber == updatedClient.accountNumber) {
			c = updatedClient;
			return clients;
		}
		
	}
}



void confirmAndUpdateClient(std::vector<stClient> clients, stClient client, std::string fileName) {
	char choice = 'n';
	std::cout << "\nDo you want to update this client? (y/n): ";
	std::string input;
	std::getline(std::cin, input);
	choice = input[0];
	if (tolower(choice) == 'y') {
		std::cout << "\nPlease Enter Updated Data for Client with Account Number: " << client.accountNumber << ": \n";
		stClient updatedClient = readUpdatedClientData(client.accountNumber);
		std::vector<stClient> updatedClients = updateClients(clients, updatedClient);
		saveUpdatedRecords(updatedClients, fileName);
		std::cout << "\nClient with Account Number (" << client.accountNumber << ") has been updated.\n";
	}
}

int main() {

	//std::vector<stClient> clients = readClients();
	std::string fileName = "clients.txt";

	//saveRecords(clients, fileName);
	//std::cout << "\nClients have been saved to file: " << fileName << std::endl;

	std::vector<stClient> clients{};
	clients = loadClientsFromFile(fileName, "#//#");
	//printClients(clients);

	std::string accountNumberToSearch = "";
	std::cout << "\nPlease Enter Account Number: ";
	std::getline(std::cin, accountNumberToSearch);

	stFoundClient foundClient = searchClientByAccountNumber(clients, accountNumberToSearch);

	if (foundClient.found) {
		printClient(foundClient.client);
		confirmAndUpdateClient(clients, foundClient.client, fileName);
		clients = loadClientsFromFile(fileName, "#//#");// to reload the updated clients list after deletion
	}
	else {
		std::cout << "\nClient with Account Number (" << accountNumberToSearch << ") not found.\n";
	}

	return 0;

}