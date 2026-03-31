#include "infrastructure/persistence/SqliteSchemaInitializer.hpp"

void SqliteSchemaInitializer::initialize(SqliteConnection& conn) {

    // clients ----------
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS clients (
            id          TEXT PRIMARY KEY,
            first_name  TEXT NOT NULL,
            last_name   TEXT NOT NULL,
            phone       TEXT NOT NULL UNIQUE,
            pin_code    TEXT NOT NULL,
            created_at  INTEGER NOT NULL,
            deleted_at  INTEGER
        );
	
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_clients_phone "
        "ON clients(phone) WHERE deleted_at IS NULL;");

    // accounts ---------
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS accounts (
            id          TEXT PRIMARY KEY,
            client_id   TEXT NOT NULL REFERENCES clients(id),
            status      TEXT NOT NULL DEFAULT 'ACTIVE',
            created_at  INTEGER NOT NULL
        );
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_accounts_client "
        "ON accounts(client_id);");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_accounts_status "
        "ON accounts(status);");

    // transactions -----------
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id          TEXT PRIMARY KEY,
            account_id  TEXT NOT NULL REFERENCES accounts(id),
            amount      INTEGER NOT NULL,
            type        TEXT NOT NULL,
            description TEXT NOT NULL,
            created_at  INTEGER NOT NULL
        );
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_transactions_account "
        "ON transactions(account_id, created_at);");

    // users --------------
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id              TEXT PRIMARY KEY,
            username        TEXT NOT NULL UNIQUE,
            password_hash   TEXT NOT NULL,
            role            TEXT NOT NULL,
            created_at      INTEGER NOT NULL,
            deleted_at      INTEGER
        );
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_users_username "
        "ON users(username) WHERE deleted_at IS NULL;");

    // outbox ---------
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS outbox (
            id              TEXT PRIMARY KEY,
            event_type      TEXT NOT NULL,
            payload         TEXT NOT NULL,
            occurred_at     INTEGER NOT NULL,
            processed_at    INTEGER,
            attempts        INTEGER NOT NULL DEFAULT 0
        );
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_outbox_pending "
        "ON outbox(occurred_at) WHERE processed_at IS NULL;");

    // audit_log ---------------
    // Append-only - UPDATE, no DELETE ever.
    conn.exec(R"(
        CREATE TABLE IF NOT EXISTS audit_log (
            id              INTEGER PRIMARY KEY AUTOINCREMENT,
            request_id      TEXT NOT NULL,
            caller_id       TEXT NOT NULL,
            operation       TEXT NOT NULL,
            outcome         TEXT NOT NULL,
            detail          TEXT NOT NULL DEFAULT '',
            ip_address      TEXT NOT NULL,
            occurred_at     INTEGER NOT NULL
        );
    )");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_audit_request "
        "ON audit_log(request_id);");

    conn.exec(

        "CREATE INDEX IF NOT EXISTS idx_audit_caller "
        "ON audit_log(caller_id, occurred_at);");
}