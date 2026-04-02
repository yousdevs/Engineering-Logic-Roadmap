#include "domain/entities/Transaction.hpp"

Transaction::Transaction(TransactionId   id,
                         AccountId       accountId,
                         Money           amount,
                         TransactionType type,
                         std::string     description,
                         std::time_t     createdAt)
    : _id(std::move(id))
    , _accountId(std::move(accountId))
    , _amount(std::move(amount))
    , _type(type)
    , _description(std::move(description))
    , _createdAt(createdAt) {}

// file scope guard shared between credit() and debit()
static void validateDescription(const std::string& description, const std::string& context) {

    if (description.empty())
        throw std::invalid_argument(context + ": description cannot be empty. "
            "Every transaction must carry an audit-friendly description.");
}

Transaction Transaction::credit(TransactionId      id,
                                const AccountId&   accountId,
                                const Money&       amount,
                                const std::string& description) {

    validateDescription(description, "Transaction::credit");

    return Transaction(
        std::move(id), accountId, amount, TransactionType::CREDIT, description, std::time(nullptr));
}

Transaction Transaction::debit(TransactionId      id,
                               const AccountId&   accountId,
                               const Money&       amount,
                               const std::string& description) {

    // Money already guards amount > 0
    validateDescription(description, "Transaction::debit");

    return Transaction(
        std::move(id), accountId, amount, TransactionType::DEBIT, description, std::time(nullptr));
}

Transaction Transaction::reconstitute(TransactionId   id,
                                      AccountId       accountId,
                                      Money           amount,
                                      TransactionType type,
                                      std::string     description,
                                      std::time_t     createdAt) {

    // No validation, data coming from persistence was valid when saved.
    return Transaction(std::move(id),
                       std::move(accountId),
                       std::move(amount),
                       type,
                       std::move(description),
                       createdAt);
}

const TransactionId& Transaction::id() const {
    return _id;
}

const AccountId& Transaction::accountId() const {
    return _accountId;
}

const Money& Transaction::amount() const {
    return _amount;
}

TransactionType Transaction::type() const {
    return _type;
}

const std::string& Transaction::description() const {
    return _description;
}

std::time_t Transaction::createdAt() const {
    return _createdAt;
}

bool Transaction::isCredit() const {
    return _type == TransactionType::CREDIT;
}

bool Transaction::isDebit() const {
    return _type == TransactionType::DEBIT;
}
