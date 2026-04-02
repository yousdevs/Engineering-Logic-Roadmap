#pragma once

#include "application/abstractions/AppError.hpp"
#include "application/abstractions/IInterceptor.hpp"

// Applied when UseCaseMetadata.requiresAuth = true
// Checks identity is present and holds the required permission.
// Use cases never check authorization - this interceptor owns that.

template<typename TRequest, typename TResponse>
class AuthorizationInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        explicit AuthorizationInterceptor(int requiredPermission) : _required(requiredPermission) {}

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            if (!ctx.isAuthenticated())
                return UseCaseResult<TResponse>::fail(
                    AppError::unauthorized("Authentication required."));

            // permission = 0 means authenticated but no specific role needed.
            if (_required != 0 && !ctx.can(_required))
                return UseCaseResult<TResponse>::fail(
                    AppError::forbidden("Insufficient permissions."));

            return next();
        }

    private:

        int _required;
};