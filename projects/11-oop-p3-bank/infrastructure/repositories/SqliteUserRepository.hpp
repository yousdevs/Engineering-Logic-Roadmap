#pragma once

#include <memory>

#include "domain/repositories/IUserRepository.hpp"

#include "infrastructure/mappers/UserMapper.hpp"
#include "infrastructure/persistence/SqliteUnitOfWork.hpp"

// remove() sets deleted_at = now() - never deletes the row.
// All standard queires filter deleted_at IS NULL.

class SqliteUserRepository : public IUserRepository {

    public:

        explicit SqliteUserRepository(std::shared_ptr<SqliteUnitOfWork> uow)
            : _uow(std::move(uow)) {}

        void save(const User& user) override;

        std::optional<User> findById(const UserId& id) override;

        bool exists(const UserId id) override;

        void remove(const UserId& id) override;

        PagedResult<User> findAll(const Page& page) override;

        std::optional<User> findByUsername(const std::string& u) override;

        bool existsByUsername(const std::string& u) override;

        int countByRole(const Role& role) override;

        std::vector<User> findDeleted() override;

    private:

        std::shared_ptr<SqliteUnitOfWork> _uow;

        SqliteConnection& db() {
            return _uow->connection();
        }
};