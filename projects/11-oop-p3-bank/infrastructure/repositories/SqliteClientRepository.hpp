#pragma once

#include <memory>

#include "domain/repositories/IClientRepository.hpp"

#include "infrastructure/mappers/ClientMapper.hpp"
#include "infrastructure/persistence/SqliteUnitOfWork.hpp"

// All queries filter deleted_at IS NULL by default.
// remove() sets deleted_at = now()  - never deletes the row.

class SqliteClientRepository : public IClientRepository {

    public:

        explicit SqliteClientRepository(std::shared_ptr<SqliteUnitOfWork> uow)
            : _uow(std::move(uow)) {}

        void save(const Client& client) override;

        std::optional<Client> findById(const ClientId& id) override;

        bool exists(const ClientId id) override;

        void remove(const ClientId& id) override;  // soft delete

        PagedResult<Client> findAll(const Page& page) override;

        PagedResult<Client> findByName(const std::string& query, const Page& page) override;

        std::optional<Client> findByPhone(const std::string& phone) override;

        bool existsByPhone(const std::string& phone) override;

        std::vector<Client> findDeleted() override;

    private:

        std::shared_ptr<SqliteUnitOfWork> _uow;
        SqliteConnection&                 db() {
            return _uow->connection();
        }
};