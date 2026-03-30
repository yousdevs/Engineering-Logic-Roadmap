#include "infrastructure/persistence/SqliteConnection.hpp"

#include <stdexcept>

SqliteConnection::SqliteConnection(const std::string& dbPath) {

    if (sqlite3_open(dbPath.c_str(), &_db) != SQLITE_OK) {

        const std::string err = sqlite3_errmsg(_db);
        sqlite3_close(_db);

        throw std::runtime_error("SqliteConnection: cannot open '" + dbPath + "': " + err);
    }

    // Enable WAL mode - better concurrent read performance.
    sqlite3_exec(_db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr);
    sqlite3_exec(_db, "PRAGMA foreign_keys=ON;", nullptr, nullptr, nullptr);
}

SqliteConnection::~SqliteConnection() {

    if (_db)
        sqlite3_close(_db);
}

void SqliteConnection::bind(sqlite3_stmt* stmt, const std::vector<std::string>& params) {

    for (int i = 0; i < static_cast<int>(params.size()); ++i) {

        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_TRANSIENT);
    }
}

void SqliteConnection::exec(const std::string& sql, const std::vector<std::string>& params) {

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {

        throw std::runtime_error("SqliteConnection::exec prepare: "
                                 + std::string(sqlite3_errmsg(_db)));
    }

    bind(stmt, params);

    const int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
        throw std::runtime_error("SqliteConnection::exec step: "
                                 + std::string(sqlite3_errmsg(_db)));
}

std::vector<Row> SqliteConnection::query(const std::string&              sql,
                                         const std::vector<std::string>& params) {

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("SqliteConnection::query prepare: "
                                 + std::string(sqlite3_errmsg(_db)));

    bind(stmt, params);

    std::vector<Row> rows;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Row row;

        const int cols = sqlite3_column_count(stmt);

        for (int i = 0; i < cols; ++i) {

            const char* name = sqlite3_column_name(stmt, i);

            if (sqlite3_column_type(stmt, i) == SQLITE_NULL) {

                row.setNull(name);
            } else {

                const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row.set(name, val ? std::string(val) : std::string{});
            }
        }

        rows.push_back(std::move(row));
    }

    sqlite3_finalize(stmt);
    return rows;
}

void SqliteConnection::beginTransaction() {

    exec("BEGIN;");
}

void SqliteConnection::commit() {

    exec("COMMIT;");
}

void SqliteConnection::rollback() {

    exec("ROLLBACK;");
}