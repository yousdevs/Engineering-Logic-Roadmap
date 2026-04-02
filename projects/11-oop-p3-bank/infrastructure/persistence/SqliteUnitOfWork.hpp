#pragma once

#include <memory>

#include "domain/ports/IUnitOfWork.hpp"

#include "infrastructure/persistence/SqliteConnection.hpp"

// Wraps a SqliteConnection transaction.
// begin()  / commit() / rollback() delegate to the connection.
// All repositories share this same connection so thier writes
// participate in the same atomic transaction.
// One instance per request - created by the CompositionRoot factory.

class SqliteUnitOfWork : public IUnitOfWork {

    public:

        explicit SqliteUnitOfWork(std::shared_ptr<SqliteConnection> connection)
            : _conn(std::move(connection)) {}

        void begin() override {

            _conn->beginTransaction();
        }

        void commit() override {

            _conn->commit();
        }

        void rollback() override {

            _conn->rollback();
        }

        // Exposes the connection so repositories can use it.
        SqliteConnection& connection() {

            return *_conn;
        }

    private:

        std::shared_ptr<SqliteConnection> _conn;
};