#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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


enum Screen {
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

Screen showLogin(AppContext& ctx) {
	return Screen::SCREEN_MAIN_MENU;
}

typedef Screen(*ScreenHandler)(AppContext&);

struct Route {
	Screen screen;
	ScreenHandler handler;
};

Route routes[] = {
	{SCREEN_LOGIN, showLogin},
	//{SCREEN_MAIN_MENU, showMainMenu},
	//{SCREEN_DEPOSIT, showDeposit},
	//{SCREEN_WITHDRAW, showWithdraw}
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


	std::cout << "Hello, world" << std::endl;
	return 0;
}