#include <iostream>

#include "domain/entities/Account.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Transaction.hpp"
#include "domain/entities/User.hpp"
#include "domain/value_objects/PinCode.hpp"

#include "application/common/UseCaseResult.hpp"
#include "application/dto/LoginRequest.hpp"
#include "application/dto/LoginResponse.hpp"
#include "application/ports/IPasswordHasher.hpp"
// #include "application/usecases/ListClientsUseCase.hpp"
#include "application/usecases/LoginUseCase.hpp"

// #include "infrastructure/persistence/FileClientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "infrastructure/security/AuthorizationService.hpp"
#include "infrastructure/security/SequentialPinCodeGenerator.hpp"
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

    User u("username", "passwordHash", "Teller");
    std::cout << "\n" << u.getUsername();

    u.changePasswordHash("22");

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

    // ListClientsUseCase listUseCase(repo, AuthorizationService());

    // ExecutionContext ctx(res.data()->getUsername(), res.data()->getRole());

    // ListClientsRequest listClientReq{};

    // auto listClientRes = listUseCase.execute(ctx, listClientReq);
    // if (listClientRes.isSuccess()) {
    //     auto clientsf = listClientRes.data()->clients;
    //     std::cout << "\n";
    //     for (auto& clientf : clientsf) {
    //         std::cout << clientf.id << " - " << clientf.name << " - "
    //                   << std::to_string(clientf.balance) << "\n";
    //     }
    // }

    SequentialIdGenerator idGenerator{};
    auto                  txId  = TransactionId::generate(idGenerator);
    auto                  accId = AccountId::generate(idGenerator);

    auto tx = Transaction::credit(txId, accId, Money::Money(100), "test");

    std::cout << "\n"
              << tx.id().value() << "|" << tx.accountId().value() << "|" << tx.amount().value()
              << "|" << (tx.isCredit() ? "Credit" : "Debit") << "|" << tx.description();

    auto clientId = ClientId::generate(idGenerator);
    auto account  = Account::openFor(accId, clientId);

    std::cout << "\n"
              << account.id().value() << "|" << account.clientId().value() << "|"
              << account.createdAt() << "|" << (account.isActive() ? "ACTIVE" : "Not ACTIVE");
    account.close();
    std::cout << "\n" << (account.isClosed() ? "CLOSED" : "Not CLOSED");

    auto pin = PinCode::from("4432");
    std::cout << "\n" << pin.value();

    try {
        auto seqPin = PinCode::from("1234");
    } catch (std::invalid_argument e) {
        std::cout << "\n" << e.what();
    }
    try {
        auto charPin = PinCode::from("add4");
    } catch (std::invalid_argument e) {
        std::cout << "\n" << e.what();
    }

    Client client1 = Client::create(ClientId::generate(idGenerator), "test", "test", "044433", pin);

    SequentialPinCodeGenerator pinGenerator{};

    std::cout << "\n"
              << client1.id().value() << "|" << client1.firstName() << "|" << client1.lastName()
              << "|" << client1.phone() << "|" << client1.pinCode().value() << "|"
              << client1.createdAt();

    client1.changePin(pinGenerator);

    std::cout << "\n"
              << client1.id().value() << "|" << client1.firstName() << "|" << client1.lastName()
              << "|" << client1.phone() << "|" << client1.pinCode().value() << "|"
              << client1.createdAt();

    client1.changePin(pinGenerator);

    try {
        client1.updatePhone("");
    } catch (std::invalid_argument e) {
        std::cout << "\n" << e.what();
    }
    client1.updatePhone("033333");
    std::cout << "\n"
              << client1.id().value() << "|" << client1.firstName() << "|" << client1.lastName()
              << "|" << client1.phone() << "|" << client1.pinCode().value() << "|"
              << client1.createdAt();

    return 0;
}