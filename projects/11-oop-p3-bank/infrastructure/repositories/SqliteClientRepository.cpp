#include "infrastructure/repositories/SqliteClientRepository.hpp"

#include <ctime>

void SqliteClientRepository::save(const Client& client) {

    const Row row = ClientMapper::toPersistence(client);

    // Upsert - insert or replace on id conflict.
    db().exec(
        "INSERT INTO clients (id, first_name, last_name, phone, pin_code, created_at, deleted_at)"
        " VALUES (?, ?, ?, ?, ?, ?, ?) "
        "ON CONFLICT(id) DO UPDATE SET "
        " first_name=excluded.first_name, last_name=excluded.last_name, "
        " phone=excluded.phone, pin_code=excluded.pin_code, "
        " deleted_at=excluded.deleted_at;",

        {row.get<std::string>("id"),
         row.get<std::string>("first_name"),
         row.get<std::string>("last_name"),
         row.get<std::string>("phone"),
         row.get<std::string>("pin_code"),
         row.get<std::string>("created_at"),
         row.isNull("deleted_at") ? ""
                                  : row.get<std::string>("deleted_at")});  // TODO: fix bind NULL
}

std::optional<Client> SqliteClientRepository::findById(const ClientId& id) {

    auto rows = db().query(

        "SELECT * FROM clients WHERE id=? AND deleted_at IS NULL;",

        {id.value()});

    if (rows.empty())
        return std::nullopt;

    return ClientMapper::toDomain(rows.front());
}

bool SqliteClientRepository::exists(const ClientId id) {

    auto rows = db().query(

        "SELECT 1 FROM clients WHERE id=? AND deleted_at IS NULL;",

        {id.value()});

    return !rows.empty();
}

void SqliteClientRepository::remove(const ClientId& id) {

    // Soft delete - sets deleted_at to current time.
    db().exec(

        "UPDATE clients SET deleted_at=? WHERE id=? AND deleted_at IS NULL;",

        {std::to_string(static_cast<long long>(std::time(nullptr))),

         id.value()});
}

PagedResult<Client> SqliteClientRepository::findAll(const Page& page) {

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM clients WHERE deleted_at IS NULL;");

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM clients WHERE deleted_at IS NULL "
        "ORDER BY created_at DESC LIMIT ? OFFSET ?;",

        {std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<Client> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(ClientMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}

PagedResult<Client> SqliteClientRepository::findByName(const std::string& query, const Page& page) {

    const std::string pattern = "%" + query + "%";

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM clients "
        "WHERE deleted_at IS NULL "
        " AND (first_name LIKE ? OR last_name LIKE ?);",

        {pattern, pattern});

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM clients "
        "WHERE deleted_at IS NULL "
        " AND (first_name LIKE ? OR last_name LIKE ?) "
        "ORDER BY last_name, first_name LIMIT ? OFFSET ?;",

        {pattern, pattern, std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<Client> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(ClientMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}

std::optional<Client> SqliteClientRepository::findByPhone(const std::string& phone) {

    auto rows = db().query(

        "SELECT * FROM clients WHERE phone=? AND deleted_at IS NULL;", {phone});

    if (rows.empty())
        return std::nullopt;

    return ClientMapper::toDomain(rows.front());
}

bool SqliteClientRepository::existsByPhone(const std::string& phone) {

    auto rows = db().query(

        "SELECT 1 FROM clients WHERE phone=? AND deleted_at IS NULL;",

        {phone});

    return !rows.empty();
}

std::vector<Client> SqliteClientRepository::findDeleted() {

    auto rows = db().query(

        "SELECT * FROM clients WHERE deleted_at IS NOT NULL "
        "ORDER BY deleted_at DESC;");

    std::vector<Client> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(ClientMapper::toDomain(r));

    return items;
}