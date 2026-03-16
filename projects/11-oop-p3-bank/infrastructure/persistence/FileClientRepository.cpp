#include "FileClientRepository.hpp"
#include "FileUtils.hpp"

#include <sstream>
#include <stdexcept>

#include "libs/StringLib.h"

FileClientRepository::FileClientRepository(const std::string& filePath) : _filePath(filePath) {}

std::vector<Client> FileClientRepository::_loadAll() const {

    std::vector<Client> clients;

    std::vector<std::string> lines = FileUtils::readLines(_filePath);

    for (const std::string& line : lines) {

        clients.push_back(_deserialize(line));
    }

    return clients;
}

void FileClientRepository::_saveAll(const std::vector<Client>& clients) {

    std::vector<std::string> lines;

    for (const Client& client : clients) {

        lines.push_back(_serialize(client));
    }

    FileUtils::writeLines(_filePath, lines);
}

Client FileClientRepository::_deserialize(const std::string& line) const {

    std::vector<std::string> parts = StringLib::split(line, "|");

    std::string accountId = parts[0];
    std::string firstName = parts[1];
    std::string lastName  = parts[2];
    std::string phone     = parts[3];
    std::string pin       = parts[4];
    long long   balance   = std::stoll(parts[5]);

    return Client(accountId, firstName, lastName, phone, pin, balance);
}

std::string FileClientRepository::_serialize(const Client& client) const {

    return StringLib::join(
        {

            client.getAccountId(),
            client.getFirstName(),
            client.getLastName(),
            client.getPhone(),
            client.getPin(),
            std::to_string(client.getBalance())},
        "|");
}

std::vector<Client> FileClientRepository::findAll() const {

    return _loadAll();
}

std::optional<Client> FileClientRepository::findById(const std::string& accountId) const {

    std::vector<Client> clients = _loadAll();

    for (Client& client : clients) {

        if (client.getAccountId() == accountId)
            return client;
    }
    return std::nullopt;
}

void FileClientRepository::save(const Client& client) {

    std::vector<Client> clients = _loadAll();

    for (Client& existing : clients) {

        if (existing.getAccountId() == client.getAccountId()) {

            existing = client;
            _saveAll(clients);
            return;
        }
    }

    clients.push_back(client);
    _saveAll(clients);
}

void FileClientRepository::remove(const std::string& accountId) {

    std::vector<Client> clients = _loadAll();
    // TODO softDelete

    clients.erase(
        std::remove_if(clients.begin(),
                       clients.end(),
                       [&](const Client& client) { return client.getAccountId() == accountId; }),
        clients.end());
    _saveAll(clients);
}
