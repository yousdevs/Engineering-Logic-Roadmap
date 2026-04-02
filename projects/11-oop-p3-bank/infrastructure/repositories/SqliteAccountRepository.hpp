#pragma once

#include <memory>

#include "domain/repositories/IAccountRepository.hpp"

#include "infrastructure/mappers/AccountMapper.hpp"
#include "infrastructure/persistence/SqliteUnitOfWork.hpp"

// No soft delete - lifecycle managed via AccountStatus column.

class SqliteAccountRepository : public IAccountRepository {

    public:

        explicit SqliteAccountRepository(std::shared_ptr<SqliteUnitOfWork> uow)
            : _uow(std::move(uow)) {}

        void save(const Account& account) override;

        std::optional<Account> findById(const AccountId& id) override;

        bool exists(const AccountId id) override;

        std::optional<Account> findByClientId(const ClientId& clientId) override;

        bool existsByClientId(const ClientId& clientId) override;

        PagedResult<Account> findByStatus(AccountStatus status, const Page& page) override;

    private:

        std::shared_ptr<SqliteUnitOfWork> _uow;

        SqliteConnection& db() {
            return _uow->connection();
        }
};