#pragma once
#include <string>

// Plain-data identity carried in ExecutionContext.
// Holds only what the application layer needs- not the domain User entity.
// Created by the session/auth middleware from a resolved token,
// never loaded directly from the repository inside a use case.

struct CallerIdentity {
        std::string userId;
        std::string username;
        std::string roleName;
        int         permissions;  // bitmask - fast permission check

        bool can(int permission) const {
            return (permissions & permission) != 0;
        }
};