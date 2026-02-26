#include <iostream>
#include <vector>
#include <iomanip>

enum enMainMenuOptions {
    SHOW_CLIENT_LIST = 1,
    ADD_NEW_CLIENT = 2,
	DELETE_CLIENT = 3,
	UPDATE_CLIENT_INFO = 4,
	FIND_CLIENT = 5,
	EXIT = 6,
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
    
}
