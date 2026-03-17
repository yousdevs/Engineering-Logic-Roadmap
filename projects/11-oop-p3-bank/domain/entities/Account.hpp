#pragma once

#include <ctime>

#include "domain/ports/IIdGenerator.hpp"
#include "domain/value_objects/AccountId.hpp"
#include "domain/value_objects/ClientId.hpp"

enum class AccountStatus { ACTIVE, FROZEN, CLOSED };

class Account {
    public:

        static Account openFor(const ClientId& clientId, IIdGenerator& idGenerator);

        static Account reconstitute(AccountId     id,
                                    ClientId      clientId,
                                    AccountStatus status,
                                    std::time_t   createdAt);

        void freeze();

        void unfreeze();

        void close();

        const AccountId& id() const;
        const ClientId&  clientId() const;
        AccountStatus    status() const;
        std::time_t      createdAt() const;

        bool isActive() const;
        bool isFrozen() const;
        bool isClosed() const;

    private:

        Account(AccountId id, ClientId clientId, AccountStatus status, std::time_t createdAt);

        AccountId     _id;
        ClientId      _clientId;
        AccountStatus _status;
        std::time_t   _createdAt;
};