#include "infrastructure/repositories/SqliteOutboxRepository.hpp"

#include <ctime>

SqliteOutboxRepository::SqliteOutboxRepository(const std::string& dbPath, std::nullptr_t)
    : _uow(nullptr), _ownConn(std::make_shared<SqliteConnection>(dbPath)) {}

SqliteConnection& SqliteOutboxRepository::db() {

    // UoW mode - share the active transactional connection.
    // Poller mode - use the dedicated read/write connection.
    return _uow ? _uow->connection() : *_ownConn;
}

OutboxEntry SqliteOutboxRepository::rowToEntry(const Row& row) {

    OutboxEntry e;
    e.id          = row.get<std::string>("id");
    e.eventType   = row.get<std::string>("event_type");
    e.payload     = row.get<std::string>("payload");
    e.occurredAt  = row.get<int64_t>("occurred_at");
    e.processedAt = row.get<std::optional<int64_t>>("processed_at");
    e.attempts    = row.get<int>("attempts");

    return e;
}

void SqliteOutboxRepository::save(const OutboxEntry& e) {

    db().exec(

        "INSERT INTO outbox (id, event_type, payload, occurred_at, processed_at, attempts) "
        "VALUES (?, ?, ?, ?, NULL, 0);",
        {e.id, e.eventType, e.payload, std::to_string(static_cast<long long>(e.occurredAt))});
}

std::vector<OutboxEntry> SqliteOutboxRepository::findPending(int limit) {

    auto rows = db().query(

        "SELECT * FROM outbox WHERE processed_at IS NULL "
        "ORDER BY occurred_at ASC LIMIT ?;",
        {std::to_string(limit)});

    std::vector<OutboxEntry> entries;
    entries.reserve(rows.size());

    for (auto& r : rows)
        entries.push_back(rowToEntry(r));

    return entries;
}

void SqliteOutboxRepository::markProcessed(const std::string& id) {

    db().exec(

        "UPDATE outbox SET processed_at=? WHERE id=?;",
        {std::to_string(static_cast<long long>(std::time(nullptr))), id});
}

void SqliteOutboxRepository::incrementAttempts(const std::string& id) {

    db().exec(

        "UPDATE outbox SET attempts = attempts + 1 WHERE id=?;", {id});
}

std::vector<OutboxEntry> SqliteOutboxRepository::findDeadLetters(int maxAttempts) {

    auto rows = db().query(

        "SELECT * FROM outbox "
        "WHERE processed_at IS NULL AND attempts >= ? "
        "ORDER BY occurred_at ASC;",
        {std::to_string(maxAttempts)});

    std::vector<OutboxEntry> entries;
    entries.reserve(rows.size());

    for (auto& r : rows)
        entries.push_back(rowToEntry(r));

    return entries;
}