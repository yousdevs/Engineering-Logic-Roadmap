#include "infrastructure/mappers/TransactionMapper.hpp"

#include <stdexcept>

Transaction TransactionMapper::toDomain(const Row& row) {

    return Transaction::reconstitute(

        TransactionId::from(row.get<std::string>("id")),
        AccountId::from(row.get<std::string>("account_id")),
        Money(static_cast<unsigned long long>(row.get<int64_t>("amount"))),
        typeFromString(row.get<std::string>("type")),
        row.get<std::string>("description"),
        row.get<int64_t>("created_at"));
}

Row TransactionMapper::toPersistence(const Transaction& tx) {

    Row row;

    row.set("id", tx.id().value());
    row.set("account_id", tx.accountId().value());
    row.set("amount", static_cast<long long>(tx.amount().value()));
    row.set("type", typeToString(tx.type()));
    row.set("description", tx.description());
    row.set("created_at", tx.createdAt());

    return row;
}

TransactionType TransactionMapper::typeFromString(const std::string& s) {

    if (s == "CREDIT")
        return TransactionType::CREDIT;

    if (s == "DEBIT")
        return TransactionType::DEBIT;

    throw std::runtime_error("TransactionMapper: unknown type '" + s + "'");
}

std::string TransactionMapper::typeToString(TransactionType t) {

    switch (t) {

        case TransactionType::CREDIT:
            return "CREDIT";
        case TransactionType::DEBIT:
            return "DEBIT";
    }

    throw std::logic_error("TransactionMapper: unhandled TransactionType");
}