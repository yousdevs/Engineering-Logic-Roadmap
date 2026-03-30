#pragma once

#include <functional>
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>

#include "infrastructure/persistence/Row.hpp"

// Thin RAII wrapper around a single SQLite connection.
// One connection per request (owned by the UnitOfWork).
// exec() - DDL / DML with no result set.
// query() - SELECT, returns rows as vector<ROW>.

class SqliteConnection {

    public:

        explicit SqliteConnection(const std::string& dbPath);

        ~SqliteConnection();

        // Not copyable - one connection, one owner.
        SqliteConnection(const SqliteConnection&) = delete;

        SqliteConnection& operator=(const SqliteConnection&) = delete;

        void exec(const std::string& sql, const std::vector<std::string>& params = {});

        std::vector<Row> query(const std::string& sql, const std::vector<std::string>& params = {});

        void beginTransaction();

        void commit();

        void rollback();

    private:

        sqlite3* _db = nullptr;

        // Binds positional text parameters to a prepared statement.
        void bind(sqlite3_stmt* stmt, const std::vector<std::string>& params);
};