#pragma once

#include <memory>
#include <string>

#include "application/abstractions/AppError.hpp"
#include "application/abstractions/IInterceptor.hpp"
#include "application/services/IRateLimiter.hpp"

// Applied when UseCaseMetadata.rateLimited = true.
// Key: ipAddress + operationName - scoped per caller per operation.
// Runs before auth so brute-force is stopped before any DB work.

template<typename TRequest, typename TResponse>
class RateLimitInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        RateLimitInterceptor(std::string operationName, std::shared_ptr<IRateLimiter> rateLimiter)
            : _operationName(std::move(operationName)), _rateLimiter(std::move(rateLimiter)) {}

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            const std::string key = ctx.ipAddress + ":" + _operationName;

            if (_rateLimiter->isLimited(key))
                return UseCaseResult<TResponse>::fail(
                    AppError::forbidden("Too many requests. Try again later."));

            _rateLimiter->increment(key);
            return next();
        }

    private:

        std::string                   _operationName;
        std::shared_ptr<IRateLimiter> _rateLimiter;
};