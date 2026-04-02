#pragma once

#include <ctime>
#include <vector>

#include "domain/entities/Transaction.hpp"
#include "domain/repositories/IRepository.hpp"
#include "domain/repositories/Page.hpp"
#include "domain/value_objects/AccountId.hpp"
#include "domain/value_objects/TransactionId.hpp"

//  Soft delete: NEVER.
//    Transactions are permanent financial records.
//    no remove().
//  save() is INSERT ONLY in the implementation.
//    A transaction is written once and never updated.

class ITransactionRepository : public IRepository<Transaction, TransactionId> {

    public:

        // Returns All transactions for an account, oldest first
        virtual std::vector<Transaction> findByAccountId(const AccountId& accountId) = 0;

        // Returns transactions within an inclusive date range, newst first.
        virtual PagedResult<Transaction> findByDateRange(const AccountId& accountId,
                                                         std::time_t      from,
                                                         std::time_t      to,
                                                         const Page&      page) = 0;

        // Returns the N most recent transactions for an account.
        virtual std::vector<Transaction> findRecentByAccountId(const AccountId& accountId,
                                                               int              limit) = 0;

        // Returns all transactions across all accounts within a date range,
        // paginated. (for audit)
        virtual PagedResult<Transaction> findAllByDateRange(std::time_t from,
                                                            std::time_t to,
                                                            const Page& page) = 0;
};