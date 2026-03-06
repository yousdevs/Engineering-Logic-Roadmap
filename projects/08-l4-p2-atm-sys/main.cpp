#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

std::vector<std::string> split(const std::string& str, const std::string& delim = " ") {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = str.find(delim);

	while (end != std::string::npos) {
		std::string word = str.substr(start, end - start);

		if (!word.empty()) {
			tokens.push_back(word);
		}

		start = end + delim.length();
		end = str.find(delim, start);
	}

	std::string lastWord = str.substr(start);
	if (!lastWord.empty()) {
		tokens.push_back(lastWord);
	}

	return tokens;
}

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

double readDouble(std::string msg = "") {
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
	return std::stod(input);
}

unsigned int readPositiveInteger() {
	int integer = 0;
	do {
		printf("Please Enter Positive Integer: ");
		integer = readValidInteger();
	} while (integer <= 0);
	return integer;
}

int readIntegerInRange(int min, int max) {
	int integer = 0;
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

void pressEnterToGoBack() {
	std::cout << "\nPress Enter to go back...";

	// Clear the Enter left in the buffer by previous inputs
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Wait for the next Enter keypress
	std::cin.get();
}

enum Screen {
	NONE,
	SCREEN_LOGIN,
	SCREEN_MAIN_MENU,
	SCREEN_QUICK_WITHDRAW,
	SCREEN_NORMAL_WITHDRAW,
	SCREEN_DEPOSIT,
	SCREEN_BALANCE_INQUIRY,
};


struct Client {
	std::string accountID = "";
	std::string pinCode = "";
	std::string name = "";
	std::string phoneNumber = "";
	long long balanceCents = 0;
};

struct AppContext {
	Client *currentClient = nullptr;
	std::vector<Client> clients{};
	
	std::string clientFilePath = "";
	std::string delim = "";
};

std::string serializeClient(const Client& client, const std::string& delim) {

	return client.accountID + delim + client.pinCode + delim +
		client.name + delim + client.phoneNumber + delim +
		std::to_string(client.balanceCents);
}

Client deserializeClient(const std::string& line, const std::string& delim) {

	Client client{};
	std::vector<std::string> splitted = split(line, delim);
	if ((splitted.size() == 5)) {
		client.accountID = splitted[0];
		client.pinCode = splitted[1];
		client.name = splitted[2];
		client.phoneNumber = splitted[3];
		client.balanceCents = std::stoll(splitted[4]);
	}

	return client;
}

void persistClients(const std::vector<Client>& clients, const std::string& filePath, const std::string& delim) {

	std::fstream file;
	file.open(filePath, std::ios::out);
	if (file.is_open()) {
		for (Client c : clients) {
				std::string line = serializeClient(c, delim);
				file << line << std::endl;
		}
		file.close();
	}
	else {
		std::cout << "\nCan't open file with path " << filePath << std::endl;
	}
}

std::vector<Client> loadClients(std::string filePath, std::string delim) {

	std::vector<Client> clients{};
	std::fstream file;
	file.open(filePath, std::ios::in);
	if (file.is_open()) {
		std::string line = "";
		while (std::getline(file, line)) {
			if (line.empty()) continue;

			Client client = deserializeClient(line, delim);
			if (!client.accountID.empty())
				clients.push_back(client);
		}
		file.close();
	}
	else {
		std::cout << "\nCan't open file with path " << filePath << std::endl;
	}
	return clients;
}

std::string createLine(short length = 40, char line = '-') {
	return  std::string(length, line);
}

void showScreenHeader(std::string headerLabel, short lineLength = 40, char lineChar = '-') {

	std::cout << std::endl;
	std::cout << createLine(lineLength, lineChar) << std::endl;
	if (headerLabel != "")
		std::cout << std::setw((lineLength/2) + (headerLabel.length()/2)) << headerLabel << std::endl;
	std::cout << createLine(lineLength, lineChar) << std::endl;
}

bool login(AppContext& ctx, std::string accoundID, std::string pinCode) {

	for (Client& c : ctx.clients) {
		if (c.accountID == accoundID && c.pinCode == pinCode) {
			ctx.currentClient = &c;
			return true;
		}
	}
	return false;
}

Screen showLogin(AppContext& ctx) {

	showScreenHeader("Login Screen");

	std::string accountID = readString("Account Number: ");
	std::string pin = readString("PIN: ");

	if (login(ctx, accountID, pin)) {
		std::cout << "Login Successful!" << std::endl;
		return Screen::SCREEN_MAIN_MENU;
	}
	
	std::cout << "Invalid Credentials." << std::endl;
	return Screen::SCREEN_LOGIN;
}

struct MenuItem {
	int option = 0;
	Screen screen = Screen::SCREEN_LOGIN;
	std::string label = "";
	long long value = 0;
};

void printMenu(const std::vector<MenuItem>& items, std::string headerLabel = "") {

	showScreenHeader(headerLabel);

	for (const MenuItem& item : items) {
		std::cout << std::setw(10) << "[" << item.option << "] " << item.label << std::endl;
	}

	std::cout << createLine() << std::endl;
	std::cout << "Please choose an option: ";
}

int readOption(const std::vector<MenuItem>& items) {
	int firstOption = items[0].option;
	int lastOption = items[items.size()-1].option;
	return readIntegerInRange(firstOption, lastOption);
}

Screen mapOptionToScreen(const std::vector<MenuItem>& items, int option) {

	for (const MenuItem& item : items) {
		if (item.option == option) {
			return item.screen;
		}
	}
	return Screen::SCREEN_MAIN_MENU;
}

Screen showMainMenu(AppContext& ctx) {

	std::vector<MenuItem> menuItems = {
		{1, Screen::SCREEN_QUICK_WITHDRAW, "Quick Withdraw"},
		{2, Screen::SCREEN_NORMAL_WITHDRAW, "Normal Withdraw"},
		{3, Screen::SCREEN_DEPOSIT, "Deposit"},
		{4, Screen::SCREEN_BALANCE_INQUIRY, "Balance Inquiry"},
		{5, Screen::SCREEN_LOGIN,   "Logout"},
	};

	printMenu(menuItems, "Main Menu");

	int choice = readOption(menuItems);

	return mapOptionToScreen(menuItems, choice);
}

double centsToDollars(long long cents) {
	return static_cast<double>(cents) / 100.0;
}

double getBalance(const Client& client) {
	return centsToDollars(client.balanceCents);
}

Screen showBalanceInquiry(AppContext& ctx) {

	showScreenHeader("Balance Inquiry Screen");

	if (!ctx.currentClient)
		return Screen::SCREEN_LOGIN;

	printf("Your Balance is: $%.2f\n", getBalance(*ctx.currentClient));

	pressEnterToGoBack();
	return Screen::SCREEN_MAIN_MENU;
}

long long dollarsToCents(double dollars) {
	return static_cast<long long> (dollars * 100.0);
}

enum TransactionType {
	Withdrawal,
	Deposit,
};

struct Transaction {
	TransactionType type = TransactionType::Withdrawal;
	long long amountInCents = 0;
	std::string validationError = "";
	bool success = false;
};

const long long ATM_WITHDRAW_STEP = 500;

Transaction executeWithdrawal(Client& client, long long amountInCents){

	Transaction tx{};
	tx.type = TransactionType::Withdrawal;
	tx.amountInCents = amountInCents;

	if (amountInCents <= 0) {
		tx.validationError = "Amount must be greater than zero.";
		return tx;
	}

	if (amountInCents % ATM_WITHDRAW_STEP != 0) {
		tx.validationError = "Amount must be a multiple of 5 dollars.";
		return tx;
	}

	if (amountInCents > client.balanceCents) {
		tx.validationError = "Amount exceeds client balance.";
		return tx;
	}

	client.balanceCents -= amountInCents;
	tx.success = true;

	return tx;
}

Transaction withdraw(AppContext& ctx, long long amountInCents){

	Transaction tx = executeWithdrawal(*ctx.currentClient, amountInCents);

	if (tx.success)
	{
		persistClients(ctx.clients, ctx.clientFilePath, ctx.delim);
	}

	return tx;
}

Screen showQuickWithdraw(AppContext& ctx) {
	
	std::vector<MenuItem> menuItems = {
		{1, Screen::NONE, "20$", 20},
		{2, Screen::NONE, "50$", 50},
		{3, Screen::NONE, "100$", 100},
		{4, Screen::SCREEN_MAIN_MENU, "Back to Menu", 0}
	};

	printMenu(menuItems, "Quick Withdraw Menu");

	int choice = readOption(menuItems);

	MenuItem selected;

	for (const MenuItem& item : menuItems)
	{
		if (item.option == choice)
		{
			selected = item;
			break;
		}
	}

	if (selected.screen != Screen::NONE)
		return selected.screen;

	long long amountInCents = dollarsToCents(selected.value);
	Transaction tx = withdraw(ctx, amountInCents);

	if (!tx.success)
		std::cout << tx.validationError << std::endl;
	else
		printf("Done Successfully. Your new balance is: $%.2f\n", getBalance(*ctx.currentClient));

	pressEnterToGoBack();
	
	return Screen::SCREEN_MAIN_MENU;
}

Screen showNormalWithdraw(AppContext& ctx) {

	showScreenHeader("Normal Withdraw Screen");
	
	double inputAmount = readDouble("Enter Amount: ");
	long long amountInCents = dollarsToCents(inputAmount);
	
	Transaction tx = withdraw(ctx, amountInCents);

	if (!tx.success)
		std::cout << tx.validationError << std::endl;
	else
		printf("Done Successfully. Your new balance is: $%.2f\n", getBalance(*ctx.currentClient));

	pressEnterToGoBack();

	return Screen::SCREEN_MAIN_MENU;
}

Transaction executeDeposit(Client& client, long long amountInCents) {

	Transaction tx{};
	tx.type = TransactionType::Deposit;
	tx.amountInCents = amountInCents;

	if (amountInCents <= 0) {
		tx.validationError = "Amount must be greater than zero.";
		return tx;
	}

	if (amountInCents % ATM_WITHDRAW_STEP != 0) {
		tx.validationError = "Amount must be a multiple of 5 dollars.";
		return tx;
	}

	client.balanceCents += amountInCents;
	tx.success = true;

	return tx;
}

Transaction deposit(AppContext& ctx, long long amountInCents) {

	Transaction tx = executeDeposit(*ctx.currentClient, amountInCents);

	if (tx.success)
	{
		persistClients(ctx.clients, ctx.clientFilePath, ctx.delim);
	}

	return tx;
}

Screen showDeposit(AppContext& ctx) {

	showScreenHeader("Deposit Screen");

	double inputAmount = readDouble("Enter Amount: ");
	long long amountInCents = dollarsToCents(inputAmount);

	Transaction tx = deposit(ctx, amountInCents);

	if (!tx.success)
		std::cout << tx.validationError << std::endl;
	else
		printf("Done Successfully. Your new balance is: $%.2f\n", getBalance(*ctx.currentClient));

	pressEnterToGoBack();

	return Screen::SCREEN_MAIN_MENU;
}

typedef Screen(*ScreenHandler)(AppContext&);

struct Route {
	Screen screen;
	ScreenHandler handler;
};

Route routes[] = {
	{SCREEN_LOGIN, showLogin},
	{SCREEN_MAIN_MENU, showMainMenu},
	{SCREEN_BALANCE_INQUIRY, showBalanceInquiry},
	{SCREEN_QUICK_WITHDRAW, showQuickWithdraw},
	{SCREEN_NORMAL_WITHDRAW, showNormalWithdraw},
	{SCREEN_DEPOSIT, showDeposit}
};

Screen dispatch(Screen screen, AppContext& ctx)
{
	for (Route& r : routes)
	{
		if (r.screen == screen)
			return r.handler(ctx);
	}
	return SCREEN_LOGIN;
}

void runApp(AppContext& ctx)
{
	Screen current = SCREEN_LOGIN;

	while (true)
	{
		current = dispatch(current, ctx);
	}
}

int main() {

	AppContext ctx{};
	ctx.clientFilePath = "clients.txt";
	ctx.delim = "#//#";
	ctx.clients = loadClients(ctx.clientFilePath, ctx.delim);
	
	runApp(ctx);

	std::cout << "Hello, world" << std::endl;
	return 0;
}