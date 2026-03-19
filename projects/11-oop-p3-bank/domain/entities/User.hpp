#pragma once

#include <ctime>
#include <stdexcept>
#include <string>

#include "domain/ports/IPasswordHasher.hpp"
#include "domain/value_objects/Role.hpp"
#include "domain/value_objects/UserId.hpp"

//  User — a system operator (bank employee)

class User {

    public:

        // Throws std::invalid_argument if username is empty.
        static User create(UserId             id,
                           const std::string& username,
                           const std::string& passwordHash,
                           Role               role);

        static User reconstitute(UserId      id,
                                 std::string username,
                                 std::string passwordHash,
                                 Role        role,
                                 std::time_t createdAt);

        // Throws std::invalid_argument if username is empty.
        void changeUsername(const std::string& username);

        // Throws std::invalid_argument if newPassword is empty.
        void changePassword(const std::string& newPassword, IPasswordHasher& hasher);

        void changeRole(const Role& role);

        bool can(int permission) const;

        const UserId&      id() const;
        const std::string& username() const;
        const std::string& passwordHash() const;
        const Role&        role() const;
        std::time_t        createdAt() const;

    private:

        User(UserId      id,
             std::string username,
             std::string passwordHash,
             Role        role,
             std::time_t createdAt);

        UserId      _id;
        std::string _username;
        std::string _passwordHash;
        Role        _role;
        std::time_t _createdAt;
};