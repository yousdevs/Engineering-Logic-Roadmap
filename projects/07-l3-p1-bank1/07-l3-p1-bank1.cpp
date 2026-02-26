#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

bool isNumber(std::string s) {
	if (s.empty()) return false;

	int start = (s[0] == '-') ? 1 : 0;
	if (start == 1 && s.length() == 1) return false; // Just a "-" is not a number

	for (int i = start; i < s.length(); i++) {
		if (!isdigit(s[i])) return false;
	}
	return true;
}

int readValidInteger() {
	std::string input = "";
	bool firstInput = true;
	do {
		if (!firstInput) {
			printf("Please enter valid integer");
		}
		else {
			firstInput = false;
		}
		std::cin >> input;
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

std::string readString(const std::string& message = "") {
	std::string input;

	if (!message.empty())
		std::cout << message;

	// Skip any leading whitespace/newlines left in the buffer
	std::getline(std::cin >> std::ws, input);

	return input;
}

enum enMainMenuOptions {
	SHOW_CLIENT_LIST = 1,
	ADD_NEW_CLIENT = 2,
	DELETE_CLIENT = 3,
	UPDATE_CLIENT_INFO = 4,
	FIND_CLIENT = 5,
	EXIT = 6,
	_FIRST_OPTION = SHOW_CLIENT_LIST,
	_LAST_OPTION = EXIT,
};

enum enScreen {
	APP_EXIT = 0,
	MAIN_MENU_SCREEN = 1,
	CLIENTS_LIST_SCREEN = 2,
	ADD_NEW_CLIENT_SCREEN = 3,
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

struct stScreenResult {
	enScreen nextScreen = APP_EXIT;
	bool dataChanged = false;
};

struct stSearchResult {
	stClient client = {};
	bool found = false;
};

stSearchResult searchClientByAccountID(const std::vector<stClient> &clients, std::string accountID){
	stClient client{};
	for (const stClient &c : clients) {
		if (c.accountID == accountID) {
			return { c, true };
		}
	}
	return { client, false };
}

void showMenu(const std::vector<stMenuItem> &menu, std::string headerLabel = "") {
	std::string line = std::string(40, '-');
	
	std::cout << line << std::endl;
	if (headerLabel != "")
		std::cout << std::setw(25) << headerLabel << std::endl;
	std::cout << line << std::endl;

	for(const stMenuItem &item : menu){
		std::cout << std::setw(10) << "[" << item.ID << "] " << item.label << std::endl;
	}

	std::cout << line << std::endl;
	std::cout << "Please choose an option: ";
}

stScreenResult showClientsScreen(const std::vector<stClient> &clients) {
	
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
	for (const stClient& client : clients) {
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
	std::cout << "Press any key to go back to main menu...\n";
	
	std::string input = "";
	std::cin >> input;
	return { MAIN_MENU_SCREEN , false};
}

stScreenResult showMainMenuScreen() {
	std::vector<stMenuItem> mainMenu = {
		{ SHOW_CLIENT_LIST, "Show Client List"},
		{ ADD_NEW_CLIENT, "Add New Client"},
		{ DELETE_CLIENT, "Delete Client"},
		{ UPDATE_CLIENT_INFO, "Update Client Info"},
		{ FIND_CLIENT, "Find Client"},
		{ EXIT, "Exit"},
	};
	showMenu(mainMenu, "Main Menu Screen");

	int option = readIntegerInRange(enMainMenuOptions::_FIRST_OPTION, enMainMenuOptions::_LAST_OPTION);
	switch (option) {
		case SHOW_CLIENT_LIST: 
			return { CLIENTS_LIST_SCREEN , false};
		case ADD_NEW_CLIENT:
			return { ADD_NEW_CLIENT_SCREEN, false };
		case EXIT:
			return { APP_EXIT, false };
		default:
			return { APP_EXIT, false };
	}

}

stClient readClientInfo(std::string accountID) {
	stClient newClient{};
	newClient.accountID = accountID;
	newClient.pinCode = readString("PIN Code: ");
	std::cout << std::endl;
	newClient.fullName = readString("Full Name: ");
	std::cout << std::endl;
	newClient.phoneNumber = readString("Phone: ");
	std::cout << std::endl;
	std::string balanceInput = readString("Balance: ");
	double balance = 0;
	balance = std::stod(balanceInput);
	newClient.accountBalance = balance;
	return newClient;
}

stScreenResult showAddNewClientScreen(std::vector<stClient>& clients) {
	std::string line = std::string(40, '-');
	std::cout << line << std::endl;
	std::cout << std::setw(10) << "Add New Clients Screen" << std::endl;
	std::cout << line << std::endl;
	std::cout << "Adding New Client" << std::endl;

	
	
	char continueAdding = 'n';
	bool clientAlreadyExist = false;
	std::string accountID = "";
	do {
		if (clientAlreadyExist) {
			accountID = readString("Client with ID [" + accountID + "] Already exist, Enter Another Account ID? ");
			std::cout << std::endl;
		}
		else {
			accountID = readString("Enter Account ID: ");
			std::cout << std::endl;
		}

		stSearchResult searchResult = searchClientByAccountID(clients, accountID);
		if (searchResult.found) {
			clientAlreadyExist = true;
		}
		else {
			clientAlreadyExist = false;
			stClient newClient = readClientInfo(accountID);
			

			clients.push_back(newClient);
			continueAdding = readString("Client Added Successfully, do you want to add more client? y/n")[0];
		}
		
	} while (std::tolower(continueAdding) == 'y' || clientAlreadyExist);

	
	return { MAIN_MENU_SCREEN, true }; // TODO: flag
}

void runApp() {

	std::vector<stClient> clients{
				{"1", "1234", "Ahmed Omar", "0543334433", 2300},
				{"1", "1234", "Ahmed Omar", "0543334433", 2300},
				{"1", "1234", "Ahmed Omar", "0543334433", 2300},
	};

	enScreen currentScreen = MAIN_MENU_SCREEN;

	while (currentScreen != enScreen::APP_EXIT) {
		switch (currentScreen) {
		case MAIN_MENU_SCREEN:
			currentScreen = showMainMenuScreen().nextScreen;
			break;
		case CLIENTS_LIST_SCREEN:
			currentScreen = showClientsScreen(clients).nextScreen;
			break;
		case ADD_NEW_CLIENT_SCREEN:
			stScreenResult res = showAddNewClientScreen(clients);
			if (res.dataChanged)
				res.dataChanged; //TODO save
			currentScreen = res.nextScreen;
			break;
		}
		
	}

}

int main()
{
	
	
	runApp();


	return 0;  
}
