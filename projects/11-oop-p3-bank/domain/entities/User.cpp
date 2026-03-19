#include "domain/entities/User.hpp"

User::User(
    UserId id, std::string username, std::string passwordHash, Role role, std::time_t createdAt)
    : _id(std::move(id))
    , _username(std::move(username))
    , _passwordHash(std::move(passwordHash))
    , _role(std::move(role))
    , _createdAt(createdAt) {}

// File-scope shared guard
static void requireNonEmpty(const std::string& value,
                            const std::string& fieldName,
                            const std::string& context) {

    if (value.empty())
        throw std::invalid_argument(context + ": " + fieldName + " cannot be empty.");
}

User User::create(UserId             id,
                  const std::string& username,
                  const std::string& passwordHash,
                  Role               role) {

    requireNonEmpty(username, "username", "User::create");
    requireNonEmpty(passwordHash, "passwordHash", "User::create");

    return User(std::move(id), username, passwordHash, std::move(role), std::time(nullptr));
}

User User::reconstitute(
    UserId id, std::string username, std::string passwordHash, Role role, std::time_t createdAt) {

    return User(
        std::move(id), std::move(username), std::move(passwordHash), std::move(role), createdAt);
}

void User::changeUsername(const std::string& username) {

    requireNonEmpty(username, "username", "User::changeUsername");
    _username = username;
}

void User::changePassword(const std::string& newPassword, IPasswordHasher& hasher) {

    requireNonEmpty(newPassword, "newPassword", "User::changePassword");

    _passwordHash = hasher.hash(newPassword);
}

void User::changeRole(const Role& role) {

    // if role was constructed, it is already valid.
    _role = role;
}

bool User::can(int permission) const {

    return _role.can(permission);
}

const UserId& User::id() const {
    return _id;
}

const std::string& User::username() const {
    return _username;
}

const std::string& User::passwordHash() const {
    return _passwordHash;
}

const Role& User::role() const {
    return _role;
}

std::time_t User::createdAt() const {
    return _createdAt;
}