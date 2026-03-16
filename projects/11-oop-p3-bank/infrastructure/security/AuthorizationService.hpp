#pragma once

#include "application/ports/IAuthorizationService.hpp"

class AuthorizationService : public IAuthorizationService {

    public:

        ~AuthorizationService() override = default;

        bool hasPermission(const std::string& role, int permission) const override;
};