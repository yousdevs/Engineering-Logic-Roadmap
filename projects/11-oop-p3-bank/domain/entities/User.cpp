#include "../entities/User.hpp"
#include <stdexcept>


User::User(
	const std::string& username,
	const std::string& passwordHash,
	int permissions)
    : _username(username), _passwordHash(passwordHash), _permissions(permissions) {}

const std::string& User::getUsername() const { return _username; }

const std::string& User::getPasswordHash() const { return _passwordHash; }

int User::getPermissions() const { return _permissions; }


bool User::hasPermission(Permission permission) const {
  return (_permissions & permission) == permission;
}

void User::addPermission(Permission permission) {
  _permissions |= permission;
}

void User::removePermission(Permission permission) {
  _permissions &= ~permission;
}

void User::changeUsername(const std::string& username) {
  if (username.empty()) throw std::invalid_argument("Username cannot be empty");

  _username = username;
}

void User::changePasswordHash(const std::string& passwordHash) {

  _passwordHash = passwordHash;
}