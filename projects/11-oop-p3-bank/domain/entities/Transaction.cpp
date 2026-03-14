#include <string>
#include <optional>
#include <ctime>
#include <stdexcept>

#include "../entities/Transaction.hpp"

Transaction::Transaction(
    const std::string& transactionId,
    std::optional<std::string> sourceAccount,
    std::optional<std::string> destinationAccount,
    long long amount,
    Type type,
    std::time_t timestamp)
    : _transactionId(transactionId),
      _sourceAccount(sourceAccount),
      _destinationAccount(destinationAccount),
      _amount(amount),
      _type(type),
      _timestamp(timestamp) {
 
    if (amount <= 0)
       throw std::invalid_argument("Transaction amount must be positive");

}


Transaction Transaction::createDeposit(
	const std::string& transactionId,
	const std::string& destinationAccount,
	long long amount
) {
  return Transaction(transactionId, std::nullopt, destinationAccount, amount,
                     Type::Deposit, std::time(nullptr));
}

Transaction Transaction::createWithdraw(
    const std::string& transactionId,
    const std::string& sourceAccount,
    long long amount) {
    
    return Transaction(transactionId, sourceAccount, std::nullopt, amount,
                     Type::Withdraw, std::time(nullptr));
}

Transaction Transaction::createTransfer(
    const std::string& transactionId,
    const std::string& sourceAccount,
    const std::string& destinationAccount,
    long long amount) {

    if (sourceAccount == destinationAccount)
        throw std::invalid_argument(
             "Source and destination accounts cannot be the same");

    return Transaction(transactionId, sourceAccount, destinationAccount, amount,
                     Type::Transfer, std::time(nullptr));
}

Transaction Transaction::rehydrate(
    const std::string& transactionId,
    std::optional<std::string> sourceAccount,
    std::optional<std::string> destinationAccount,
    long long amount,
    Type type,
    std::time_t timestamp) {
    
    return Transaction(transactionId, sourceAccount, destinationAccount, amount,
                     type, timestamp);
}

const std::optional<std::string>& Transaction::getSourceAccount() const {
    
    return _sourceAccount;
}

const std::optional<std::string>& Transaction::getDestinationAccount() const {

    return _destinationAccount;
}

const std::string& Transaction::getTransactionId() const {

    return _transactionId;
}

std::time_t Transaction::getTimestamp() const {
    
    return _timestamp;
}

Transaction::Type Transaction::getType() const {
    
    return _type;
}

long long Transaction::getAmount() const {

    return _amount;
}