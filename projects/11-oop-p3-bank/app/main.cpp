#include <iostream>
#include "../domain/entities/Client.hpp"

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
    
    return 0;
}