#pragma once

#include <string>
#include <vector>

#include "domain/entities/Client.hpp"
#include "domain/repositories/IRepository.hpp"
#include "domain/repositories/Page.hpp"
#include "domain/value_objects/ClientId.hpp"

//  All queries below exclude soft-deleted records unless
//  explicitly noted (findDeleted).

class IClientRepository : public IRepository<Client, ClientId> {

    public:

        // Paginated list of all active clients, newest first.
        virtual PagedResult<Client> findAll(const Page& page) = 0;

        // Full-text search by first name, last name, or both.
        virtual PagedResult<Client> findByName(const std::string& query, const Page& page) = 0;

        // Finds an active Client by phone.
        virtual std::optional<Client> findByPhone(const std::string& phone) = 0;

        // Returns true if an active client exists with this phone
        virtual bool existsByPhone(const std::string& phone) = 0;

        // Returns soft-deleted clients, newest deletion first.
        virtual std::vector<Client> findDeleted() = 0;

        // Soft delete.
        virtual void remove(const ClientId& id) = 0;
};