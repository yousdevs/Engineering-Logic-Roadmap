#pragma once

#include <vector>

#include "domain/entities/Transaction.hpp"

class ITransactionRepository {

    public:

        virtual ~ITransactionRepository() = default;

        virtual void save(const Transaction& transaction) = 0;

        virtual std::vector<Transaction> findAll() const = 0;

        virtual std::vector<Transaction> findByAccountId(const std::string& accountId) const = 0;
};