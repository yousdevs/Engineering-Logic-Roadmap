#pragma once

#include "application/abstractions/AppError.hpp"
#include "application/abstractions/IInterceptor.hpp"

// Calls request.validate() before the use case runs.
// Always active - no metadata flag needed.
// Short-circuits with ValidationFailed if any error is returned.

template<typename TRequest, typename TResponse>
class ValidationInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            auto errors = request.validate();

            if (!errors.empty())
                return UseCaseResult<TResponse>::fail(
                    AppError::validation(errors.front().message, errors.front().field));

            return next();
        }
};