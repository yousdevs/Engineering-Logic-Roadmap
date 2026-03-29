#pragma once

#include "domain/entities/Account.hpp"

#include "infrastructure/persistence/Row.hpp"

class AccountMapper {

    public:

        static Account toDomain(const Row& row);

        static Row toPersistence(const Account& account);

    private:

        static AccountStatus statusFromString(const std::string& s);

        static std::string statusToString(AccountStatus s);
};