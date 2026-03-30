#include "infrastructure/repositories/SqliteAccountRepository.hpp"

void SqliteAccountRepository::save(const Account& account) {

    const Row row = AccountMapper::toPersistence(account);

    db().exec(

        "INSERT INTO accounts (id, client_id, status, created_at) "
        "VALUES (?, ?, ?, ?) "
        "ON CONFLICT(id) DO UPDATE SET status=excluded.status;",

        {row.get<std::string>("id"),
         row.get<std::string>("client_id"),
         row.get<std::string>("status"),
         row.get<std::string>("created_at")});
}

std::optional<Account> SqliteAccountRepository::findById(const AccountId& id) {

    auto rows = db().query(

        "SELECT * FROM accounts WHERE id=?;", {id.value()});

    if (rows.empty())
        return std::nullopt;

    return AccountMapper::toDomain(rows.front());
}

bool SqliteAccountRepository::exists(const AccountId id) {

    auto rows = db().query(

        "SELECT 1 FROM accounts WHERE id=?;", {id.value()});

    return !rows.empty();
}

std::optional<Account> SqliteAccountRepository::findByClientId(const ClientId& clientId) {

    auto rows = db().query(

        "SELECT * FROM accounts WHERE client_id=?;", {clientId.value()});

    if (rows.empty())
        return std::nullopt;

    return AccountMapper::toDomain(rows.front());
}

bool SqliteAccountRepository::existsByClientId(const ClientId& clientId) {

    auto rows = db().query(

        "SELECT 1 FROM accounts WHERE client_id=?;", {clientId.value()});

    return !rows.empty();
}

PagedResult<Account> SqliteAccountRepository::findByStatus(AccountStatus status, const Page& page) {

    const std::string s =
        AccountMapper::statusToString(status);  // reuse private helper via friend or expose

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM accounts WHERE status=?;", {s});

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM accounts WHERE status=? "
        "ORDER BY created_at DESC LIMIT ? OFFSET ?;",

        {s, std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<Account> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(AccountMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}