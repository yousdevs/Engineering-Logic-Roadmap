#include "domain/entities/User.hpp"

#include <stdexcept>

User::User(const std::string& username, const std::string& passwordHash, const std::string& role)
    : _username(username), _passwordHash(passwordHash), _role(role) {}

const std::string& User::getUsername() const {
    return _username;
}

const std::string& User::getPasswordHash() const {
    return _passwordHash;
}

const std::string& User::getRole() const {
    return _role;
}

void User::changeUsername(const std::string& username) {
    if (username.empty())
        throw std::invalid_argument("Username cannot be empty");

    _username = username;
}

void User::changePasswordHash(const std::string& passwordHash) {

    _passwordHash = passwordHash;
}

void User::changeRole(const std::string& role) {

    _role = role;
}