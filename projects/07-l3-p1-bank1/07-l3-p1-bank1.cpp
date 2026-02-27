#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>

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

int readValidInteger() {
	std::string input = "";
	bool firstInput = true;
	do {
		if (!firstInput) {
			printf("Please enter valid integer\n");
		}
		else {
			firstInput = false;
		}
		input = readString();
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
	DELETE_CLIENT_SCREEN = 4,
};

enum enClientStatus {
	ACTIVE = 1,
	DELETED = 2,
};

struct stClient {
	std::string accountID = "";
	std::string pinCode = "";
	std::string fullName = "";
	std::string phoneNumber = "";
	double accountBalance = 0.0;
	enClientStatus status = ACTIVE;
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

std::string serializeClient(const stClient &client, const std::string &delim) {
	return client.accountID + delim + client.pinCode + delim +
		client.fullName + delim + client.phoneNumber + delim +
		std::to_string(client.accountBalance);
}

stClient deserializeClient(const std::string &line, const std::string& delim) {
	stClient client{};
	std::vector<std::string> splitted = split(line, delim);
	if ((splitted.size() == 5)) {
		client.accountID = splitted[0];
		client.pinCode = splitted[1];
		client.fullName = splitted[2];
		client.phoneNumber = splitted[3];
		client.accountBalance = std::stod(splitted[4]);
	}

	return client;
}

void persistClients(const std::vector<stClient>& clients, const std::string& filePath, const std::string& delim) {
	std::fstream file;
	file.open(filePath, std::ios::out);
	if (file.is_open()) {
		for (stClient c : clients) {
			if (c.status == ACTIVE) {
				std::string line = serializeClient(c, delim);
				file << line << std::endl;
			}
		}
		file.close();
	}
	else {
		std::cout << "\nCan't open file with path " << filePath << std::endl;
	}
}

std::vector<stClient> loadClients(std::string filePath, std::string delim) {
	std::vector<stClient> clients{};
	std::fstream file;
	file.open(filePath, std::ios::in);
	if (file.is_open()) {
		std::string line = "";
		while (std::getline(file, line)) {
			if (line.empty()) continue;

			stClient client = deserializeClient(line, delim);
			if (!client.accountID.empty())   // avoid pushing invalid clients
				clients.push_back(client);
		}
		file.close();
	}
	else {
		std::cout << "\nCan't open file with path " << filePath << std::endl;
	}
	return clients;
}


stSearchResult searchClientByAccountID(const std::vector<stClient> &clients, std::string accountID){
	stClient client{};
	for (const stClient &c : clients) {
		if (c.accountID == accountID) {
			return { c, true };
		}
	}
	return { client, false };
}

bool deleteClientByAccountID(std::vector<stClient>& clients, const std::string& accountID) {
	for (stClient& client : clients) {
		if (client.accountID == accountID && client.status == ACTIVE) {
			client.status = DELETED;
			return true;
		}
	}
	return false;
}

bool isAccountIDTaken(const std::vector<stClient>& clients, const std::string& accountID) {
	return searchClientByAccountID(clients, accountID).found;
}

std::string promptForUniqueAccountID(const std::vector<stClient>& clients) {
	std::string accountID;
	do {
		accountID = readString("Enter Account ID: ");
		if (isAccountIDTaken(clients, accountID)) {
			std::cout << "Client with ID [" << accountID << "] already exists.";
		}
		else break;
	} while (true);
	return accountID;
}

std::string createLine(short length = 40, char line = '-') {
	return  std::string(length, line);
}

void showScreenHeader(std::string headerLabel, short lineLength = 40, char lineChar = '-') {
	
	std::cout << std::endl;
	std::cout << createLine(lineLength, lineChar) << std::endl;
	if (headerLabel != "")
		std::cout << std::setw(25) << headerLabel << std::endl;
	std::cout << createLine(lineLength, lineChar) << std::endl;
}

void showMenu(const std::vector<stMenuItem> &menu, std::string headerLabel = "") {
	
	showScreenHeader(headerLabel);

	for(const stMenuItem &item : menu){
		std::cout << std::setw(10) << "[" << item.ID << "] " << item.label << std::endl;
	}

	std::cout << createLine() << std::endl;
	std::cout << "Please choose an option: ";
}

int countActiveClients(const std::vector<stClient>& clients) {
	int counter = 0;
	for (const stClient& c : clients) {
		if (c.status == ACTIVE) counter++;
	}
	return counter;
}

stScreenResult showClientsScreen(const std::vector<stClient> &clients) {
	
	std::string clientList = "Client List (" + std::to_string(countActiveClients(clients)) + ") Client(s).\n";

	std::cout << "\n" << std::setw(75) << clientList;
	std::cout << createLine(120) << std::endl;

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

	std::cout << createLine(120) << std::endl;

	// Data
	for (const stClient& client : clients) {
		if (client.status == ACTIVE) {
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
	}

	std::cout << createLine(120) << std::endl;
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
		case DELETE_CLIENT:
			return { DELETE_CLIENT_SCREEN, false };
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
	std::cout << "Balance: ";
	newClient.accountBalance = readValidInteger();
	return newClient;
}

stScreenResult showAddNewClientScreen(std::vector<stClient>& clients) {
	showScreenHeader("Add New Client Screen");

	bool dataChanged = false;
	char continueAdding = 'y';

	while (std::tolower(continueAdding) == 'y') {
		std::string accountID = promptForUniqueAccountID(clients);
		stClient newClient = readClientInfo(accountID);

		clients.push_back(newClient);
		dataChanged = true;

		std::string more = readString("Client added. Add another? (y/n): ");
		continueAdding = more.empty() ? 'n' : more[0];
	}

	return { MAIN_MENU_SCREEN, dataChanged };
}

void printClientDetails(const stClient& client) {
	std::cout << "\nClient Details\n";
	std::cout << createLine() << "\n";

	std::cout << std::left << std::setw(15) << "Account ID:"
		<< std::right << client.accountID << "\n";

	std::cout << std::left << std::setw(15) << "PIN Code:"
		<< std::right << client.pinCode << "\n";

	std::cout << std::left << std::setw(15) << "Name:"
		<< std::right << client.fullName << "\n";

	std::cout << std::left << std::setw(15) << "Phone:"
		<< std::right << client.phoneNumber << "\n";

	std::cout << std::left << std::setw(15) << "Balance:"
		<< std::right << client.accountBalance << "\n";

	std::cout << createLine() << "\n";

	// reset formatting
	std::cout << std::endl;
}

stScreenResult showDeleteClientScreen(std::vector<stClient>& clients) {
	
	showScreenHeader("Delete Client Screen");

	bool dataChanged = false;

	std::string accountID = readString("Enter Account ID: ");
	stSearchResult res = searchClientByAccountID(clients, accountID);
	if (res.found && res.client.status == ACTIVE) {
		printClientDetails(res.client);
		std::string input = readString("Are You Sure To Delete This Client ? y/n  ");
		char choice = 'n';
		if (!input.empty()) {
			choice = input[0];
		}
		if (std::tolower(choice) == 'y') {
			dataChanged = deleteClientByAccountID(clients, accountID);
			(dataChanged) ? 
				std::cout << "Client Deleted Successfully." << std::endl
			: 
				std::cout << "Failed To Delete Client." << std::endl;
		}
	}
	else {
		std::cout << "Client with account ID (" << accountID << ") was not Found!" << std::endl;
	}
	std::cout << "Type any key and hit enter to go back to Main Menu .." << std::endl;
	std::string input = readString("");

	return { MAIN_MENU_SCREEN, dataChanged };
}


void runApp() {

	const std::string PERSISTENCE_FILE_PATH = "clients.txt";
	const std::string RECORDS_DELIM = "#//#";
	std::vector<stClient> clients{};
	clients = loadClients(PERSISTENCE_FILE_PATH, RECORDS_DELIM);
	enScreen currentScreen = MAIN_MENU_SCREEN;

	while (currentScreen != enScreen::APP_EXIT) {
		switch (currentScreen) {
		case MAIN_MENU_SCREEN:
			currentScreen = showMainMenuScreen().nextScreen;
			break;
		case CLIENTS_LIST_SCREEN:
			currentScreen = showClientsScreen(clients).nextScreen;
			break;
		case ADD_NEW_CLIENT_SCREEN: {
			stScreenResult res = showAddNewClientScreen(clients); //mutation
			if (res.dataChanged)
				persistClients(clients, PERSISTENCE_FILE_PATH, RECORDS_DELIM);
			currentScreen = res.nextScreen;
			break;
		}
		case DELETE_CLIENT_SCREEN: { 
			stScreenResult res = showDeleteClientScreen(clients); //possibly mutation
			if (res.dataChanged)
				persistClients(clients, PERSISTENCE_FILE_PATH, RECORDS_DELIM);
			currentScreen = res.nextScreen;
			break;
		}
		default:  currentScreen = MAIN_MENU_SCREEN ;
		}
		
	}

}

int main()
{
	
	
	runApp();


	return 0;  
}
