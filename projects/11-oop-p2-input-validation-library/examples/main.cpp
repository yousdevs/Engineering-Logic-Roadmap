#include "InputValidationLib.h"



int main() {

	using std::cout;
	using std::endl;

    std::cout << "===== Input Validation Library Demo =====\n\n";

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

    // Read integer
    std::cout << "Enter an integer: ";
    int number = InputValidationLib::readInt();

    std::cout << "You entered: " << number << "\n\n";


    // Read integer within range
    std::cout << "Enter a number between 1 and 10: ";
    int rangedInt = InputValidationLib::readIntInRange(1, 10);

    std::cout << "Valid number: " << rangedInt << "\n\n";


    // Read double
    std::cout << "Enter a decimal number: ";
    double dbl = InputValidationLib::readDouble();

    std::cout << "You entered: " << dbl << "\n\n";


    // Read double within range
    std::cout << "Enter a decimal between 0.0 and 1.0: ";
    double rangedDouble = InputValidationLib::readDoubleInRange(0.0, 1.0);

    std::cout << "Valid value: " << rangedDouble << "\n\n";

    std::cout << "\nDemo finished.\n";
}