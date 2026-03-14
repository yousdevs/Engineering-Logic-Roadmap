#include <iostream>
#include "../domain/entities/Client.hpp"
#include "../domain/entities/User.hpp"
#include "../domain/entities/Transaction.hpp"
#include "../infrastructure/persistence/FileClientRepository.hpp"

int main()
{
    std::cout << "Bank System Starting..." << std::endl;
    
    Client c("1", "Omer", "Khaled", "1234", "3333", 4);
    std::cout << c.getAccountId();
    c.changeFirstName("Ahmed");
    std::cout << "\n" << c.getFullName() << "\n";
    std::cout << "\n" << c.getFirstName() << "\n";
    std::cout << "\n" << c.getLastName() << "\n";
    std::cout << "\n" << c.getPhone() << "\n";
    
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

    FileClientRepository repo(DATA_PATH "clients.txt");

    std::cout << "\n=== All Clients ===\n";

    auto clients = repo.findAll();

    for (const auto& c : clients) {
      std::cout << c.getAccountId() << " | " << c.getFullName() << " | "
                << c.getPhone() << " | " << c.getBalance() << "\n";
    }

    std::cout << "\n=== Find Client C001 ===\n";

    auto client = repo.findById("C001");

    if (client) {
      std::cout << client->getFullName() << " found\n";
    } else {
      std::cout << "Client not found\n";
    }
    std::cout << "\n=== Add New Client ===\n";

    Client newClient("C003", "Bob", "Marley", "5553333", "9999", 1500);

    try {
      repo.save(newClient);
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }

    std::cout << "Client added.\n";

    std::cout << "\n=== After Insert ===\n";

    clients = repo.findAll();

    for (const auto& c : clients) {
      std::cout << c.getAccountId() << " | " << c.getFullName() << " | "
                << c.getPhone() << " | " << c.getBalance() << "\n";
    }

    std::cout << "\n=== Remove C002 ===\n";

    try {
      repo.remove("C002");
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }

    clients = repo.findAll();

    std::cout << "\n=== After Remove ===\n";

    for (const auto& c : clients) {
      std::cout << c.getAccountId() << " | " << c.getFullName() << " | "
                << c.getPhone() << " | " << c.getBalance() << "\n";
    }
    

    return 0;
}