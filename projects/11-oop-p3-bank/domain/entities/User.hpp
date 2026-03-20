#pragma once

#include <ctime>
#include <optional>
#include <stdexcept>
#include <string>

#include "domain/ports/IPasswordHasher.hpp"
#include "domain/value_objects/Role.hpp"
#include "domain/value_objects/UserId.hpp"

//  User — a system operator (bank employee)
//  Soft delete:
//    deletedAt absent  → active user
//    deletedAt present → deactivated user
//    Deactivated users cannot log in or perform actions.
//    Their records are retained for audit trail integrity —
//    every past action references their UserId.

class User {

    public:

        // Throws std::invalid_argument if username is empty.
        static User create(UserId             id,
                           const std::string& username,
                           const std::string& passwordHash,
                           Role               role);

        static User reconstitute(UserId                     id,
                                 std::string                username,
                                 std::string                passwordHash,
                                 Role                       role,
                                 std::time_t                createdAt,
                                 std::optional<std::time_t> deletedAt);

        // Throws std::logic_error if already deleted.
        void softDelete();

        bool isDeleted() const;

        // Throws std::invalid_argument if username is empty.
        // Throws std::logic_error if user is deleted.
        void changeUsername(const std::string& username);

        // Throws std::invalid_argument if newPassword is empty.
        // Throws std::logic_error if user is deleted.
        void changePassword(const std::string& newPassword, IPasswordHasher& hasher);

        // Throws std::logic_error if user is deleted.
        void changeRole(const Role& role);

        bool can(int permission) const;

        const UserId&              id() const;
        const std::string&         username() const;
        const std::string&         passwordHash() const;
        const Role&                role() const;
        std::time_t                createdAt() const;
        std::optional<std::time_t> deletedAt() const;

    private:

        User(UserId                     id,
             std::string                username,
             std::string                passwordHash,
             Role                       role,
             std::time_t                createdAt,
             std::optional<std::time_t> deletedAt);

        UserId                     _id;
        std::string                _username;
        std::string                _passwordHash;
        Role                       _role;
        std::time_t                _createdAt;
        std::optional<std::time_t> _deletedAt;
};