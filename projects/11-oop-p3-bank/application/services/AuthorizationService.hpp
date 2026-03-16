#pragma once

#include <domain/security/Roles.hpp>
#include <string>

class AuthorizationService {

    public:

        static bool hasPermission(const std::string& role, int permission) {

            return (permissionFromRole(role) & permission) == permission;
        }
};