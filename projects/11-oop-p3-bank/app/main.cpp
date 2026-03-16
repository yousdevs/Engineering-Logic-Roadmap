#include <iostream>
#include "../domain/entities/Client.hpp"
#include "../domain/entities/User.hpp"
#include "../domain/entities/Transaction.hpp"
#include "../infrastructure/persistence/FileClientRepository.hpp"
#include "../infrastructure/persistence/FileUserRepository.hpp"
#include "../libs/StringLib.h"
#include "application/usecases/LoginUseCase.hpp"
#include "application/ports/IPasswordHasher.hpp"
#include "application/dto/LoginResult.hpp"

class DumpPasswordHasher : public IPasswordHasher {
 public:
  DumpPasswordHasher() {}
     bool verify(const std::string& pass, const std::string& hash) {
    return pass == hash;
  }
     std::string hash(const std::string& pass) { return pass;}
};

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

    User u("username", "passwordHash", "Teller");
    std::cout << "\n" << u.getUsername();

    
    u.changePasswordHash("22");

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
    
    FileUserRepository usersRepo(DATA_PATH "users.txt");

    std::cout << "\n=== All Users ===\n";

    auto users = usersRepo.findAll();

    for (const auto& u : users) {
      std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | "
                << u.getRole() << "\n";
    }

    std::cout << "\n=== Find User U001 ===\n";

    auto user = usersRepo.findByUsername("U001");

    if (user) {
      std::cout << user->getUsername() << " found\n";
    } else {
      std::cout << "User not found\n";
    }
    std::cout << "\n=== Add New User ===\n";

    User newUser("U003", "Bobhashhash", "Admin");

    try {
      usersRepo.save(newUser);
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }

    std::cout << "User added.\n";

    std::cout << "\n=== After Insert ===\n";

    users = usersRepo.findAll();

    for (const auto& u : users) {
      std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | "
                << u.getRole() << "\n";
    }

    std::cout << "\n=== Remove U002 ===\n";

    try {
      usersRepo.remove("U002");
    } catch (std::invalid_argument& e) {
      std::cout << "\n" << e.what();
    }

    users = usersRepo.findAll();

    std::cout << "\n=== After Remove ===\n";

    for (const auto& u : users) {
      std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | "
                << u.getRole() << "\n";
    }


    std::cout << StringLib::join({"hello", "world"}, ", ");


    DumpPasswordHasher hasher;
    LoginUseCase loginUS(usersRepo, hasher);
    
    LoginResult res = loginUS.execute("U003", "Bobhashhash");//U003|Bobhashhash|Admin

    if (!res.success){
      std::cout << "\n" << res.message;
    } else {
    
        std::cout << "\n"
                << res.message << "\n"
                << res.user->username << "\n"
                << res.user->role;
    }


    return 0;
}