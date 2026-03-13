#include "Client.hpp"
#include <stdexcept>

Client::Client(
    const std::string& accountId,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& phone,
    const std::string& pin,
    long long balance)
    : _accountId(accountId),
    _firstName(firstName),
    _lastName(lastName),
    _phone(phone),
    _pin(pin),
    _balance(balance)
{
}

const std::string& Client::getAccountId() const { return _accountId; }
const std::string& Client::getFirstName() const { return _firstName; }
const std::string& Client::getLastName() const { return _lastName; }
const std::string& Client::getPhone() const { return _phone; }
const std::string& Client::getPin() const { return _pin; }
long long Client::getBalance() const { return _balance; }

const std::string& Client::getFullName() const {
    return _firstName + " " + _lastName;
}

void Client::changeFirstName(const std::string& firstName) {
    _firstName = firstName;
}

void Client::changeLastName(const std::string& lastName) {
    _lastName = lastName;
}

void Client::changePhone(const std::string& phone) {
    _phone = phone;
}

void Client::changePin(const std::string& pin) {
    _pin = pin;
}

void Client::deposit(long long amount) {
    if (amount <= 0)
        throw std::invalid_argument("Deposit amount must be positive");
    
    _balance += amount;
}

void Client::withdraw(long long amount) {
    if (amount <= 0)
        throw std::invalid_argument("Withdraw amount must be positive");

    if (amount > _balance)
        throw std::runtime_error("Insufficient balance");

    _balance -= amount;
}

