#pragma once

#include <stdexcept>

#include "application/context/ExecutionContext.hpp"
#include "application/ports/IAuthorizationService.hpp"

class UseCase {

    protected:

        const IAuthorizationService& _authorizationService;

        explicit UseCase(const IAuthorizationService& authorizationService)
            : _authorizationService(authorizationService) {}

        void ensurePermission(const ExecutionContext& context, int permission) const {

            if (!_authorizationService.hasPermission(context.getRole(), permission)) {

                throw std::runtime_error("Permission denied");
            }
        }

    public:

        virtual ~UseCase()                 = default;
        UseCase(const UseCase&)            = delete;
        UseCase& operator=(const UseCase&) = delete;
};