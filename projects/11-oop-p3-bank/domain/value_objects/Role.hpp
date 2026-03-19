#pragma once

#include <stdexcept>
#include <string>

#include "domain/security/Permissions.hpp"

//  Value Object rules:
//    - Immutable after construction.
//    - Equality is by value (permission bitmask), not identity.
//    - Two Roles with the same permissions are the same Role.
//

class Role {

    public:

        static Role admin();
        static Role teller();
        static Role viewer();

        // deserialization constructor, restors a role from persistence
        // Throws std::invalid_argument for unknown role names
        static Role from(const std::string& roleName);

        bool can(int permission) const;

        // returns the canonical name of the role 'Admin' etc
        const std::string& name() const;

        // returns the full permission bitmask
        int permissions() const;

        bool operator==(const Role& other) const;
        bool operator!=(const Role& other) const;

    private:

        Role(std::string name, int permissions);

        std::string _name;
        int         _permissions;
};
