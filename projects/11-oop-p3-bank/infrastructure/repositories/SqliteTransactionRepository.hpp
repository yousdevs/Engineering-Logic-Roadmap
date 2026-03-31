#pragma once

#include <memory>

#include "domain/repositories/ITransactionRepository.hpp"

#include "infrastructure/mappers/TransactionMapper.hpp"
#include "infrastructure/persistence/SqliteUnitOfWork.hpp"

// INSERT-only - save() never updates existing raws.

class SqliteTransactionRepository : public ITransactionRepository {

    public:

        explicit SqliteTransactionRepository(std::shared_ptr<SqliteUnitOfWork> uow)
            : _uow(std::move(uow)) {}

        void save(const Transaction& tx) override;

        std::optional<Transaction> findById(const TransactionId& id) override;

        bool exists(const TransactionId id) override;

        std::vector<Transaction> findByAccountId(const AccountId& id) override;

        PagedResult<Transaction> findByDateRange(const AccountId& id,
                                                 std::time_t      from,
                                                 std::time_t      to,
                                                 const Page&      page) override;

        std::vector<Transaction> findRecentByAccountId(const AccountId& id, int limit) override;

        PagedResult<Transaction> findAllByDateRange(std::time_t from,
                                                    std::time_t to,
                                                    const Page& page) override;

    private:

        std::shared_ptr<SqliteUnitOfWork> _uow;

        SqliteConnection& db() {
            return _uow->connection();
        }
};