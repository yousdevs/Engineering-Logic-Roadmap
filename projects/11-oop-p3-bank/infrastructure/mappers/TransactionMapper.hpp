#pragma once

#include <cstdint>

#include "domain/entities/Transaction.hpp"

#include "infrastructure/persistence/Row.hpp"

// INSERT-only mapper - toPersistence() is called once at creation.
// No update, no delete - ever.

class TransactionMapper {

    public:

        static Transaction toDomain(const Row& row);

        static Row toPersistence(const Transaction& tx);

    private:

        static TransactionType typeFromString(const std::string& s);

        static std::string typeToString(TransactionType t);
};