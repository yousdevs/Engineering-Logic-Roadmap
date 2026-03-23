#pragma once

#include <memory>

#include "domain/ports/IUnitOfWork.hpp"

#include "application/abstractions/IUseCase.hpp"
#include "application/abstractions/UseCaseMetadata.hpp"
#include "application/abstractions/UseCasePipeline.hpp"
#include "application/audit/IAuditLog.hpp"
#include "application/services/IRateLimiter.hpp"

// Services the builder may inject into interceptors.
struct PipelineServices {

        std::shared_ptr<IAuditLog>    auditLog;
        std::shared_ptr<IUnitOfWork>  unitOfWork;
        std::shared_ptr<IRateLimiter> rateLimiter;
};

// Reads UseCaseMetadata and assembles only the interceptors needed.
// This is the NestJS metadata-driven decorator pattern in C++.
//
// Fixed interceptor order (always respected):
//  1. CallerPolicyInterceptor  - reject wrong caller type
//  2. ValidationInterceptor    - always on, validate request fields
//  3. RateLimitInterceptor     - if rateLimited = true
//  4. AuthorizationInterceptor - if requiresAuth = true

#include "application/interceptors/AuthorizationInterceptor.hpp"
#include "application/interceptors/CallerPolicyInterceptor.hpp"
#include "application/interceptors/RateLimitInterceptor.hpp"
#include "application/interceptors/ValidationInterceptor.hpp"

class PipelineBuilder {

    public:

        template<typename TRequest, typename TResponse>
        static UseCasePipeline<TRequest, TResponse> build(
            std::shared_ptr<IUseCase<TRequest, TResponse>> useCase,
            const PipelineServices&                        services) {

            const auto                           meta = useCase->metadata();
            UseCasePipeline<TRequest, TResponse> pipeline(useCase);

            pipeline.addInterceptor(
                std::make_shared<CallerPolicyInterceptor<TRequest, TResponse>>(meta.callerPolicy));

            pipeline.addInterceptor(std::make_shared<ValidationInterceptor<TRequest, TResponse>>());

            if (meta.rateLimited)
                pipeline.addInterceptor(std::make_shared<RateLimitInterceptor<TRequest, TResponse>>(
                    meta.name, services.rateLimiter));

            if (meta.requiresAuth)
                pipeline.addInterceptor(
                    std::make_shared<AuthorizationInterceptor<TRequest, TResponse>>(
                        meta.permission));

            return pipeline;
        }
};