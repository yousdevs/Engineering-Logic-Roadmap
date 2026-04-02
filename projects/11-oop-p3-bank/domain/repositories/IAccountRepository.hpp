#pragma once

#include <vector>

#include "domain/entities/Account.hpp"
#include "domain/repositories/IRepository.hpp"
#include "domain/repositories/Page.hpp"
#include "domain/value_objects/AccountId.hpp"
#include "domain/value_objects/ClientId.hpp"

//  Soft delete: NOT NEEDED.
//    Account lifecycle is fully modeled by AccountStatus.
//    CLOSED is the terminal state.
//    remove() is = delete — use account.close() instead.

class IAccountRepository : public IRepository<Account, AccountId> {

    public:

        // Finds the account belonging to this client.
        virtual std::optional<Account> findByClientId(const ClientId& clientId) = 0;

        // Returns true if an account exists for this client.
        virtual bool existsByClientId(const ClientId& clientId) = 0;

        // Returns all accounts with the given status, paginated.
        virtual PagedResult<Account> findByStatus(AccountStatus status, const Page& page) = 0;
};