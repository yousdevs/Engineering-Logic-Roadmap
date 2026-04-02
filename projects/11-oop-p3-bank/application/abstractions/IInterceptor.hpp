#pragma once

#include <functional>

#include "application/abstractions/ExecutionContext.hpp"
#include "application/abstractions/UseCaseResult.hpp"

// Pipeline stage - mirrors NestJS NestInterceptor.
// next() runs the remainder of the chain ( next interceptor or usecase).
// An interceptor may: short-circuit, wrap or pass through.

template<typename TRequest, typename TResponse>
class IInterceptor {

    public:

        using NextFn = std::function<UseCaseResult<TResponse>()>;

        virtual UseCaseResult<TResponse> intercept(const ExecutionContext& ctx,
                                                   const TRequest&         request,
                                                   NextFn                  next) = 0;

        virtual ~IInterceptor() = default;
};