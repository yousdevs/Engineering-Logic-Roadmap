#pragma once

#include <string>

class Client {
	
private:
    std::string _accountId;
    std::string _firstName;
    std::string _lastName;
    std::string _phone;
    std::string _pin;
    long long _balance;

public:
    Client(
        const std::string& accountId,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& phone,
        const std::string& pin,
        long long balance
    );
    
    const std::string& getAccountId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhone() const;
    const std::string& getPin() const;
    long long getBalance() const;

    const std::string getFullName() const;

    void changeFirstName(const std::string& firstName);
    void changeLastName(const std::string& lastName);
    void changePhone(const std::string& phone);
    void changePin(const std::string& pin);
    
    /**
     * @brief Deposits a positive amount into the account.
     * @param amount The value to add to the balance.
     * @exception std::invalid_argument Thrown if amount is zero or negative.
     */
    void deposit(long long amount);

    /**
     * @brief Withdraws a positive amount from the account.
     * @param amount The value to remove from the balance.
     * @exception std::invalid_argument Thrown if amount is zero or negative.
     * @exception std::runtime_error Thrown if amount exceeds current balance.
     */
    void withdraw(long long amount);
};