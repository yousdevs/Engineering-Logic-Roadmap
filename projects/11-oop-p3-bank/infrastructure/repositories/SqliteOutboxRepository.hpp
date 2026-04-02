#pragma once

#include <memory>

#include "application/outbox/IOutboxRepository.hpp"

#include "infrastructure/persistence/SqliteUnitOfWork.hpp"

// save() is called inside the active transaction - atomic with domain saves.
// findPending/markProcessed/incrementAttempts use their own connection
// because the OutboxPoller runs on a background thread outside any UoW.

class SqliteOutboxRepository : public IOutboxRepository {

    public:

        // Two constructors - one for in-transaction writes (UoW connection),
        // one for the poller (its own dedicated connection).
        explicit SqliteOutboxRepository(std::shared_ptr<SqliteUnitOfWork> uow)
            : _uow(std::move(uow)), _ownConn(nullptr) {}

        SqliteOutboxRepository(const std::string& dbPath, std::nullptr_t /* poller mode */);

        void save(const OutboxEntry& entry) override;

        std::vector<OutboxEntry> findPending(int limit) override;

        void markProcessed(const std::string& id) override;

        void incrementAttempts(const std::string& id) override;

        std::vector<OutboxEntry> findDeadLetters(int maxAttempts) override;

    private:

        std::shared_ptr<SqliteUnitOfWork> _uow;      // null in poller mode
        std::shared_ptr<SqliteConnection> _ownConn;  // null in UoW mode

        SqliteConnection&  db();
        static OutboxEntry rowToEntry(const Row& row);
};