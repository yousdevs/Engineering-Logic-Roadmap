#include "infrastructure/security/SimplePasswordHasher.hpp"

#include <functional>
#include <string>

std::string SimplePasswordHasher::hash(const std::string& password) {

    std::hash<std::string> hasher;

    return std::to_string(hasher(password));
}

bool SimplePasswordHasher::verify(const std::string& password, const std::string& passwordHash) {

    return this->hash(password) == passwordHash;
}