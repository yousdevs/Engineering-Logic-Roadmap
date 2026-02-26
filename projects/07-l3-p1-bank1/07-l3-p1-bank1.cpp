#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

enum enMainMenuOptions {
    SHOW_CLIENT_LIST = 1,
    ADD_NEW_CLIENT = 2,
	DELETE_CLIENT = 3,
	UPDATE_CLIENT_INFO = 4,
	FIND_CLIENT = 5,
	EXIT = 6,
};

struct stClient {
	std::string accountID = "";
	std::string pinCode = "";
	std::string fullName = "";
	std::string phoneNumber = "";
	double accountBalance = 0.0;
};

struct stMenuItem {
	short ID;
	std::string label;
};

void showMenu(std::vector<stMenuItem> menu, std::string headerLabel = "") {
	std::string line = std::string(40, '-');
	
	std::cout << line << std::endl;
	if (headerLabel != "")
		std::cout << std::setw(25) << headerLabel << std::endl;
	std::cout << line << std::endl;

	for(stMenuItem item : menu){
		std::cout << std::setw(10) << "[" << item.ID << "] " << item.label << std::endl;
	}

	std::cout << line << std::endl;
	std::cout << "Please choose an option: ";
}

void showClientsScreen(std::vector<stClient> clients) {
	
	std::string clientList = "Client List (" + std::to_string(clients.size()) + ") Client(s).\n";
	std::string line = std::string(120, '-') + "\n";

	std::cout << "\n" << std::setw(75) << clientList;
	std::cout << line;

	// Header
	std::cout << "|"
		<< std::left << std::setw(19) << "Account ID"
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
			<< std::left << std::setw(19) << client.accountID
			<< "|"
			<< std::left << std::setw(19) << client.pinCode
			<< "|"
			<< std::left << std::setw(29) << client.fullName
			<< "|"
			<< std::right << std::setw(19) << client.phoneNumber
			<< "|"
			<< std::right << std::setw(14) << client.accountBalance
			<< "|\n";
	}

	std::cout << line;
	std::cout << "Press any key to go back to main menu...";
}

int main()
{
	std::vector<stMenuItem> mainMenu = {
		{ SHOW_CLIENT_LIST, "Show Client List"},
		{ ADD_NEW_CLIENT, "Add New Client"},
		{ DELETE_CLIENT, "Delete Client"},
		{ UPDATE_CLIENT_INFO, "Update Client Info"},
		{ FIND_CLIENT, "Find Client"},
		{ EXIT, "Exit"},
	};
	showMenu(mainMenu, "Main Menu");

	std::vector<stClient> clients{
		{"1", "1234", "Ahmed Omar", "0543334433", 2300},
		{"1", "1234", "Ahmed Omar", "0543334433", 2300},
		{"1", "1234", "Ahmed Omar", "0543334433", 2300},
	};
	showClientsScreen(clients);
	return 0;
    
}
