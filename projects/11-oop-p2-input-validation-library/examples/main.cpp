#include "InputValidationLib.h"



int main() {

	using std::cout;
	using std::endl;

    // Read text
    std::cout << "Enter your name: ";
    std::string name = InputValidationLib::readLine();

    std::cout << "Hello " << name << "\n\n";


    // Yes/No input
    bool result = InputValidationLib::readYesNo("Do you want to continue? (y/n): ");

    if (result)
        std::cout << "User chose YES\n";
    else
        std::cout << "User chose NO\n";

}