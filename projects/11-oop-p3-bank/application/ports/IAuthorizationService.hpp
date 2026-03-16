#pragma once

#include <string>

class IAuthorizationService {

    public:

        virtual ~IAuthorizationService() = default;

        // TODO: replace int with Permission enum class once domain/security/Permission.hpp is
        // stable
        virtual bool hasPermission(const std::string& role, int permission) const = 0;
};