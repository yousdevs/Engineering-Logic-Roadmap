#include <iostream>
#include "../domain/entities/Client.hpp"
#include "../domain/entities/User.hpp"
#include "../domain/entities/Transaction.hpp"

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

    Transaction tx = Transaction::createDeposit("1", "acc1", 40);
    std::cout << "\n" << tx.getAmount();
    std::string src = tx.getDestinationAccount().value();
    std::cout << "\n" << src;
    std::string dst = "No Account";
    if (tx.getSourceAccount().has_value()) {
      dst = tx.getSourceAccount().value();
    }
    std::cout << "\n" << dst;
    
    try {
      Transaction tx2 = Transaction::createDeposit("2", "Acc2", 0);
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }
    return 0;
}