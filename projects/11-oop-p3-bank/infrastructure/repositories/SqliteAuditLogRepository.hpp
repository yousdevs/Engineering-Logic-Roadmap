#pragma once

#include <memory>

#include "application/audit/IAuditLog.hpp"

#include "infrastructure/persistence/SqliteConnection.hpp"

// Writes audite entries to the audit_log table using its own connection.
// Audit writes must never be rolled back by the UoW - they use a
// separate connection so they commit independently.
// Even failed use cases produce an audit record.

class SqliteAuditLogRepository : public IAuditLog {

    public:

        explicit SqliteAuditLogRepository(const std::string& dbPath)
            : _conn(std::make_shared<SqliteConnection>(dbPath)) {}

        void record(const AuditEntry& entry) override;

    private:

        std::shared_ptr<SqliteConnection> _conn;
};