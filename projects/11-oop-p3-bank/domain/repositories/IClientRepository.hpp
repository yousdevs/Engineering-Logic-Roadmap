#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../entities/Client.hpp"

class IClientRepository {

 public:
	virtual ~IClientRepository() = default;

	virtual std::vector<Client> findAll() const = 0;

	/**
    * @brief Finds a specific client by their unique account ID.
    * @param accountId The ID to search for.
    * @return An optional containing the Client if found, std::nullopt
    * otherwise.
    */
	virtual std::optional<Client> findById(const std::string& accountId) const = 0;
	
	virtual void save(const Client& client) = 0;

	virtual void remove(const std::string& accountId) = 0;
};