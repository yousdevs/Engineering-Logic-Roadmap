#pragma once

#include <stdexcept>

#include "application/common/UseCaseResult.hpp"
#include "application/context/ExecutionContext.hpp"
#include "application/ports/IAuthorizationService.hpp"

class UseCase {

    protected:

        const IAuthorizationService& _authorizationService;

        explicit UseCase(const IAuthorizationService& authorizationService)
            : _authorizationService(authorizationService) {}

        UseCaseResult<void> checkPermission(const ExecutionContext& context, int permission) const {

            if (!_authorizationService.hasPermission(context.getRole(), permission)) {

                return UseCaseResult<void>::failure("Permission denied");
            }

            return UseCaseResult<void>::success();
        }

    public:

        virtual ~UseCase()                 = default;
        UseCase(const UseCase&)            = delete;
        UseCase& operator=(const UseCase&) = delete;
};