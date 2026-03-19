#pragma once

#include <optional>
#include <string>
#include <vector>

#include "domain/entities/User.hpp"
#include "domain/repositories/IRepository.hpp"
#include "domain/repositories/Page.hpp"
#include "domain/value_objects/UserId.hpp"

//  All queries below exclude soft-deleted users unless
//  explicitly noted (findDeleted).

class IUserRepository : public IRepository<User, UserId> {

    public:

        // Paginated list of all active users.
        virtual PagedResult<User> findAll(const Page& page) = 0;

        // Finds an active user by username.
        virtual std::optional<User> findByUsername(const std::string& username) = 0;

        // Returns true if an active user exists with this username.
        virtual bool existsByUsername(const std::string& username) = 0;

        // Returns count of active users with Admin role.
        // Use case: DeactivateUserUseCase — must refuse if this
        // would deactivate the last Admin, locking out the system.
        virtual int countByRole(const Role& role) = 0;

        // Returns soft-deleted users, newest deactivation first.
        virtual std::vector<User> findDeleted() = 0;
};