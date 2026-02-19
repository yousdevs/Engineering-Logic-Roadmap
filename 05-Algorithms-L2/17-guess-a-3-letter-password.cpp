#include <iostream>
#include <string>

std::string readPassword() {
	std::string password;
	std::cout << "Please enter the password: " << std::endl;
	std::cin >> password;
	return password;
}


bool guessPassword(std::string password) {
	int start = char('A');
	int end = char('Z');
	std::string guess = "";
	int attempts = 0;
	for (int i = start; i <= end; i++) {
		for (int j = start; j <= end; j++) {
			for (int k = start; k <= end; k++) {
				guess += char(i);
				guess += char(j);
				guess += char(k);
				attempts++;
				std::cout << "Trail [" << attempts << "] : " << guess << std::endl;
				if (guess == password) {
					std::cout << "\n - Password found! \n Password is: " << guess 
						<< "\n Found after " << attempts << " Trail(s)." << std::endl;
					return true;
				}
				else {
					std::cout << std::endl;
				}
				guess = "";
			}
		}
	}
	std::cout << "\n - Password not found! " << std::endl;
	return false;
}



int main() {
	guessPassword(readPassword());
	return 0;
}