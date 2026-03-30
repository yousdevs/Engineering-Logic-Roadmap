#include "infrastructure/mappers/AccountMapper.hpp"

Account AccountMapper::toDomain(const Row& row) {

    return Account::reconstitute(AccountId::from(row.get<std::string>("id")),
                                 ClientId::from(row.get<std::string>("client_id")),
                                 statusFromString(row.get<std::string>("status")),
                                 row.get<int64_t>("created_at"));
}

Row AccountMapper::toPersistence(const Account& a) {

    Row row;

    row.set("id", a.id().value());
    row.set("client_id", a.clientId().value());
    row.set("status", statusToString(a.status()));
    row.set("created_at", a.createdAt());

    return row;
}

AccountStatus AccountMapper::statusFromString(const std::string& s) {

    if (s == "ACTIVE")
        return AccountStatus::ACTIVE;

    if (s == "FROZEN")
        return AccountStatus::FROZEN;

    if (s == "CLOSED")
        return AccountStatus::CLOSED;

    throw std::runtime_error("AccountMapper: unknown status '" + s + "'");
}

std::string AccountMapper::statusToString(AccountStatus s) {

    switch (s) {

        case AccountStatus::ACTIVE:
            return "ACTIVE";
        case AccountStatus::FROZEN:
            return "FROZEN";
        case AccountStatus::CLOSED:
            return "CLOSED";
    }

    throw std::logic_error("AccountMapper: unhandled AccountStatus");
}