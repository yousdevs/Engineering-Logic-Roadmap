#pragma once

#include <optional>
#include <string>
#include <vector>

#include "domain/entities/User.hpp"

class IUserRepository {
    public:

        virtual ~IUserRepository() = default;

        virtual std::vector<User> findAll() const = 0;

        /**
         * @brief Finds a specific User by their unique username.
         * @param username The username ID to search for.
         * @return An optional containing the User if found, std::nullopt
         * otherwise.
         */
        virtual std::optional<User> findByUsername(const std::string& username) const = 0;

        virtual void save(const User& user) = 0;

        virtual void remove(const std::string& username) = 0;
};