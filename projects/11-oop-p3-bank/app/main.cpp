#include <iostream>

#include "domain/entities/Client.hpp"
#include "domain/entities/Transaction.hpp"
#include "domain/entities/User.hpp"

#include "application/common/UseCaseResult.hpp"
#include "application/dto/LoginRequest.hpp"
#include "application/dto/LoginResponse.hpp"
#include "application/ports/IPasswordHasher.hpp"
#include "application/usecases/ListClientsUseCase.hpp"
#include "application/usecases/LoginUseCase.hpp"

#include "infrastructure/persistence/FileClientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "infrastructure/security/AuthorizationService.hpp"
#include "infrastructure/security/SimplePasswordHasher.hpp"
#include "infrastructure/services/SequentialIdGenerator.hpp"

#include "libs/StringLib.h"

class DumpPasswordHasher : public IPasswordHasher {
    public:

        DumpPasswordHasher() {}
        bool verify(const std::string& pass, const std::string& hash) {
            return pass == hash;
        }
        std::string hash(const std::string& pass) {
            return pass;
        }
};

int main() {
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
    } catch (std::invalid_argument& e) {
        std::cout << e.what();
    }

    User u("username", "passwordHash", "Teller");
    std::cout << "\n" << u.getUsername();

    u.changePasswordHash("22");

    FileClientRepository repo(DATA_PATH "clients.txt");

    std::cout << "\n=== All Clients ===\n";

    auto clients = repo.findAll();

    for (const auto& c : clients) {
        std::cout << c.getAccountId() << " | " << c.getFullName() << " | " << c.getPhone() << " | "
                  << c.getBalance() << "\n";
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
        std::cout << c.getAccountId() << " | " << c.getFullName() << " | " << c.getPhone() << " | "
                  << c.getBalance() << "\n";
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
        std::cout << c.getAccountId() << " | " << c.getFullName() << " | " << c.getPhone() << " | "
                  << c.getBalance() << "\n";
    }

    FileUserRepository usersRepo(DATA_PATH "users.txt");

    std::cout << "\n=== All Users ===\n";

    auto users = usersRepo.findAll();

    for (const auto& u : users) {
        std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | " << u.getRole()
                  << "\n";
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
        std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | " << u.getRole()
                  << "\n";
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
        std::cout << u.getUsername() << " | " << u.getPasswordHash() << " | " << u.getRole()
                  << "\n";
    }

    std::cout << StringLib::join({"hello", "world"}, ", ");

    SimplePasswordHasher hasher;
    LoginUseCase         loginUS(usersRepo, hasher);

    UseCaseResult<LoginResponse> res =
        loginUS.execute(LoginRequest{"U001", "12345678"});  // U003|12345678hash|Admin

    if (!res.isSuccess()) {
        std::cout << "\n" << res.message();
    } else {

        std::cout << "\n" << "\n" << res.data()->getUsername() << "\n" << res.data()->getRole();
    }

    std::cout << "\n" << hasher.hash("12345678");

    ListClientsUseCase listUseCase(repo, AuthorizationService());

    ExecutionContext ctx(res.data()->getUsername(), res.data()->getRole());

    ListClientsRequest listClientReq{};

    auto listClientRes = listUseCase.execute(ctx, listClientReq);
    if (listClientRes.isSuccess()) {
        auto clientsf = listClientRes.data()->clients;
        std::cout << "\n";
        for (auto& clientf : clientsf) {
            std::cout << clientf.id << " - " << clientf.name << " - "
                      << std::to_string(clientf.balance) << "\n";
        }
    }

    SequentialIdGenerator idGenerator{};
    auto                  txId  = TransactionId::generate(idGenerator);
    auto                  accId = AccountId::generate(idGenerator);

    auto tx = Transaction::credit(txId, accId, Money::Money(100), "test");

    std::cout << "\n"
              << tx.id().value() << "|" << tx.accountId().value() << "|" << tx.amount().value()
              << "|" << (tx.isCredit() ? "Credit" : "Debit") << "|" << tx.description();
    return 0;
}