#include "infrastructure/repositories/SqliteUserRepository.hpp"

#include <ctime>

void SqliteUserRepository::save(const User& user) {

    const Row row = UserMapper::toPersistence(user);

    db().exec(

        "INSERT INTO users (id, username, password_hash, role, created_at, deleted_at) "
        "VALUES (?, ?, ?, ?, ?, ?) "
        "ON CONFLICT(id) DO UPDATE SET "
        " username=excluded.username, "
        " password_hash=excluded.password_hash, "
        " role=excluded.role, "
        " deleted_at=excluded.deleted_at;",

        {row.get<std::string>("id"),
         row.get<std::string>("username"),
         row.get<std::string>("password_hash"),
         row.get<std::string>("role"),
         row.get<std::string>("created_at"),
         row.isNull("deleted_at") ? "" : row.get<std::string>("deleted_at")});
}

std::optional<User> SqliteUserRepository::findById(const UserId& id) {

    auto rows = db().query(

        "SELECT * FROM users WHERE id=? AND deleted_at IS NULL;", {id.value()});

    if (rows.empty())
        return std::nullopt;

    return UserMapper::toDomain(rows.front());
}

bool SqliteUserRepository::exists(const UserId id) {

    auto rows = db().query(

        "SELECT 1 FROM users WHERE id=? AND deleted_at IS NULL;", {id.value()});

    return !rows.empty();
}

void SqliteUserRepository::remove(const UserId& id) {

    db().exec(

        "UPDATE users SET deleted_at=? WHERE id=? AND deleted_at IS NULL;",
        {std::to_string(static_cast<long long>(std::time(nullptr))), id.value()});
}

PagedResult<User> SqliteUserRepository::findAll(const Page& page) {

    auto countRows = db().query(

        "SELECT COUNT(*) AS n FROM users WHERE deleted_at IS NULL;");

    const int total = std::stoi(countRows.front().get<std::string>("n"));

    auto rows = db().query(

        "SELECT * FROM users WHERE deleted_at IS NULL "
        "ORDER BY username ASC LIMIT ? OFFSET ?;",
        {std::to_string(page.limit), std::to_string(page.offset)});

    std::vector<User> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(UserMapper::toDomain(r));

    return {std::move(items), total, page.offset, page.limit};
}

std::optional<User> SqliteUserRepository::findByUsername(const std::string& username) {

    auto rows = db().query(

        "SELECT * FROM users WHERE username=? AND deleted_at IS NULL;", {username});

    if (rows.empty())
        return std::nullopt;

    return UserMapper::toDomain(rows.front());
}

bool SqliteUserRepository::existsByUsername(const std::string& username) {

    auto rows = db().query(

        "SELECT 1 FROM users WHERE username=? AND deleted_at IS NULL;", {username});

    return !rows.empty();
}

int SqliteUserRepository::countByRole(const Role& role) {

    auto rows = db().query(

        "SELECT COUNT(*) AS n FROM users "
        "WHERE role=? AND deleted_at IS NULL;",
        {role.name()});

    return std::stoi(rows.front().get<std::string>("n"));
}

std::vector<User> SqliteUserRepository::findDeleted() {

    auto rows = db().query(

        "SELECT * FROM users WHERE deleted_at IS NOT NULL "
        "ORDER BY deleted_at DESC;");

    std::vector<User> items;
    items.reserve(rows.size());

    for (auto& r : rows)
        items.push_back(UserMapper::toDomain(r));

    return items;
}