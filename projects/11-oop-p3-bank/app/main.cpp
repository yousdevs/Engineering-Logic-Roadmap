#include <iostream>

#include "domain/entities/Account.hpp"
#include "domain/entities/Client.hpp"
#include "domain/entities/Transaction.hpp"
#include "domain/entities/User.hpp"
#include "domain/ports/IPasswordHasher.hpp"
#include "domain/services/BalanceCalculator.hpp"
#include "domain/value_objects/PinCode.hpp"

#include "infrastructure/persistence/FileUserRepository.hpp"
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

    std::cout << StringLib::join({"hello", "world"}, ", ");

    SimplePasswordHasher hasher;

    SequentialIdGenerator idGenerator{};

    UserId user1Id   = UserId::generate(idGenerator);
    Role   user1Role = Role::admin();

    User user1 = User::create(user1Id, "user1", hasher.hash("hashedPassword"), user1Role);

    std::cout << "\n"
              << user1.id().value() << "|" << user1.username() << "|" << user1.passwordHash() << "|"
              << user1.role().name() << "|" << user1.createdAt();

    auto txId  = TransactionId::generate(idGenerator);
    auto accId = AccountId::generate(idGenerator);

    auto tx  = Transaction::credit(txId, accId, Money::Money(100), "test");
    auto tx1 = Transaction::credit(txId, accId, Money::Money(100), "test");
    auto tx2 = Transaction::credit(txId, accId, Money::Money(100), "test");

    std::vector<Transaction> txs     = {tx, tx1, tx2};
    Money                    balance = BalanceCalculator().calculate(accId, txs);
    std::cout << "\nBalance total for: " << accId.value() << " is " << balance.value();

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