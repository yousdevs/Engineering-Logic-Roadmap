#include "infrastructure/mappers/UserMapper.hpp"

User UserMapper::toDomain(const Row& row) {

    return User::reconstitute(UserId::from(row.get<std::string>("id")),
                              row.get<std::string>("username"),
                              row.get<std::string>("password_hash"),
                              Role::from(row.get<std::string>("role")),
                              row.get<int64_t>("created_at"),
                              row.get<std::optional<int64_t>>("deleted_at"));
}

Row UserMapper::toPersistence(const User& u) {

    Row row;

    row.set("id", u.id().value());
    row.set("username", u.username());
    row.set("password_hash", u.passwordHash());
    row.set("role", u.role().name());
    row.set("created_at", u.createdAt());

    u.deletedAt().has_value() ? row.set("deleted_at", u.deletedAt().value())
                              : row.setNull("deleted_at");

    return row;
}