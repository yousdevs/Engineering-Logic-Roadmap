#include "../entities/User.hpp"
#include <stdexcept>


User::User(
	const std::string& username,
	const std::string& password,
	int permissions)
    : _username(username), _password(password), _permissions(permissions) {}

const std::string& User::getUsername() const { return _username; }

int User::getPermissions() const { return _permissions; }
bool User::verifyPassword(const std::string& password) const {
  return _password == password;
}

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

void User::changePassword(const std::string& password) {
  if (password.length() < 4) throw std::invalid_argument("Password too short");

  _password = password;
}