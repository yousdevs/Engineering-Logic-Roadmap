#include "FileUserRepository.hpp"
#include "../../domain/entities/User.hpp"
#include "FileUtils.hpp"

#include <vector>
#include <optional>
#include <sstream>
#include <stdexcept>

FileUserRepository::FileUserRepository(const std::string& filePath)
    : _filePath(filePath) {}

std::vector<User> FileUserRepository::_loadAll() const {

    std::vector<User> users;

    std::vector<std::string> lines = FileUtils::readLines(_filePath);

    for (const std::string& line : lines) {
      
        if (!line.empty()) users.push_back(_deserialize(line));
    }

    return users;

}

void FileUserRepository::_saveAll(const std::vector<User>& users) {

    std::vector<std::string> lines;

    for (const User& user : users) {
    
        lines.push_back((_serialize(user)));
     
    }

    FileUtils::writeLines(_filePath, lines);
}

User FileUserRepository::_deserialize(const std::string& line) const{

    std::stringstream ss(line);

    std::string username;

    std::string passwordHash;

    std::string permissionsStr;

    std::getline(ss, username, '|');
    std::getline(ss, passwordHash, '|');
    std::getline(ss, permissionsStr, '|');

    int permissions = std::stoi(permissionsStr);

    return User(username, passwordHash, permissions);
}

std::string FileUserRepository::_serialize(const User& user) const {

    return user.getUsername() + "|" + user.getPasswordHash() +
         "|" +
         std::to_string(user.getPermissions());

}

std::vector<User> FileUserRepository::findAll() const { return _loadAll(); }

std::optional<User> FileUserRepository::findByUsername(
    const std::string& username) const {

    std::vector<User> users = _loadAll();

    for (const User& user : users) {
    
        if (user.getUsername() == username) {
           return user;
        }
    }

    return std::nullopt;

}

void FileUserRepository::save(const User& user) {

    std::vector<User> users = _loadAll();

    for (User& existing : users) {
    
        if (existing.getUsername() == user.getUsername()) {
      
            existing = user;
            _saveAll(users);
            return;
        }
    }

    users.push_back(user);
    _saveAll(users);

}

void FileUserRepository::remove(const std::string& username) {

    std::vector<User> users = _loadAll();

    users.erase(std::remove_if(users.begin(), users.end(), // TODO soft delete
                                 [&](const User& user) {
                                   return user.getUsername() == username;
                                 }),
                  users.end());
    
    _saveAll(users);
}