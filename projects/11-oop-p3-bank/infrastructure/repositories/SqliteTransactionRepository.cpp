#include "infrastructure/repositories/SqliteTransactionRepository.hpp"

void SqliteTransactionRepository::save(const Transaction& tx) {

    const Row row = TransactionMapper::toPersistence(tx);

    // INSERT only - transactions are immutable. No ON CONFLICT update.
    db().exec(

        "INSERT INTO transactions (id, account_id, amount, type, description, created_at)"
        " VALUES (?, ?, ?, ?, ?, ?);",

        {row.get<std::string>("id"),
         row.get<std::string>("account_id"),
         row.get<std::string>("amount"),
         row.get<std::string>("type"),
         row.get<std::string>("description"),
         row.get<std::string>("created_at")});
}

std::optional<Transaction> SqliteTransactionRepository::findById(const TransactionId& id) {

    auto rows = db().query(

        "SELECT * FROM transactions WHERE id=?;", {id.value()});

    if (rows.empty())
        return std::nullopt;

    return TransactionMapper::toDomain(rows.front());
}

bool SqliteTransactionRepository::exists(const TransactionId id) {

    auto rows = db().query(

        "SELECT 1 FROM transactions WHERE id=?;", {id.value()});

    return !rows.empty();
}

std::vector<Transaction> SqliteTransactionRepository::findByAccountId(const AccountId& id) {

    auto rows = db().query(

        "SELECT * FROM transactions WHERE account_id=? "
        "ORDER BY created_at ASC;",  // oldest first - for BalanceCalculator
        {id.value()});

    std::vector<Transaction> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(TransactionMapper::toDomain(r));

    return items;
}

PagedResult<Transaction> SqliteTransactionRepository::findByDateRange(const AccountId& id,
                                                                      std::time_t      from,
                                                                      std::time_t      to,
                                                                      const Page&      page) {

    const std::string sFrom = std::to_string(static_cast<long long>(from));
    const std::string sTo   = std::to_string(static_cast<long long>(to));

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM transactions "
        "WHERE account_id=? AND created_at BETWEEN ? AND ?;",
        {id.value(), sFrom, sTo});

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM transactions "
        "WHERE account_id=? AND created_at BETWEEN ? AND ? "
        "ORDER BY created_at DESC LIMIT ? OFFSET ?;",

        {id.value(), sFrom, sTo, std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<Transaction> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(TransactionMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}

std::vector<Transaction> SqliteTransactionRepository::findRecentByAccountId(const AccountId& id,
                                                                            int limit) {

    auto rows = db().query(

        "SELECT * FROM transactions WHERE account_id=? "
        "ORDER BY created_at DESC LIMIT ?;",

        {id.value(), std::to_string(limit)}

    );

    std::vector<Transaction> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(TransactionMapper::toDomain(r));

    return items;
}

PagedResult<Transaction> SqliteTransactionRepository::findAllByDateRange(std::time_t from,
                                                                         std::time_t to,
                                                                         const Page& page) {

    const std::string sFrom = std::to_string(static_cast<long long>(from));
    const std::string sTo   = std::to_string(static_cast<long long>(to));

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM transactions "
        "WHERE created_at BETWEEN ? AND ?;",
        {sFrom, sTo});

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM transactions WHERE created_at BETWEEN ? AND ? "
        "ORDER BY created_at DESC LIMIT ? OFFSET ?;",
        {sFrom, sTo, std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<Transaction> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(TransactionMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}