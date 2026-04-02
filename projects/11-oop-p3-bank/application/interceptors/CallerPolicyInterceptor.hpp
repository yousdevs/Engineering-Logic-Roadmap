#pragma once

#include "application/abstractions/AppError.hpp"
#include "application/abstractions/CallerType.hpp"
#include "application/abstractions/IInterceptor.hpp"

// Enforces CallerPolicy - runs first in every pipeline.
// Rejects incompatible caller types before any other work is done.
// ATMOnly policy exists now so future ATM use cases need no change here.

template<typename TRequest, typename TResponse>
class CallerPolicyInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        explicit CallerPolicyInterceptor(CallerPolicy policy) : _policy(policy) {}

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            if (!isAllowed(ctx))
                return UseCaseResult<TResponse>::fail(
                    AppError::forbidden("Caller type not permitted for this operation."));

            return next();
        }

    private:

        CallerPolicy _policy;

        bool isAllowed(const ExecutionContext& ctx) const {

            switch (_policy) {

                case CallerPolicy::AnyCallerType:

                    return true;

                case CallerPolicy::AnyAuthenticated:

                    return ctx.isAuthenticated();

                case CallerPolicy::PublicOnly:

                    return !ctx.isAuthenticated();

                case CallerPolicy::ATMOnly:

                    return ctx.callerType == CallerType::ATM;
            }

            return false;
        }
};