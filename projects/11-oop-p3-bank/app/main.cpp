#include <iostream>
#include "../domain/entities/Client.hpp"
#include "../domain/entities/User.hpp"

int main()
{
    std::cout << "Bank System Starting..." << std::endl;
    
    Client c("1", "", "", "", "", 4);
    std::cout << c.getAccountId();
    c.changeFirstName("Ahmed");
    std::cout << "\n" << c.getFirstName() << "\n";
    
    try {
        c.deposit(0);
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what();
    }

    User u("username", "password", 2);
    std::cout << "\n" << u.getUsername();

    try {
      u.changePassword("22");
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }
    if (u.verifyPassword("password")) {
      std::cout << "\n" << "Password correct";
    }
    return 0;
}