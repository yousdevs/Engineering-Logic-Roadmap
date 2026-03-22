#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "application/abstractions/IInterceptor.hpp"
#include "application/abstractions/IUseCase.hpp"

// Chains interceptors around a use case - mirrors NestJS request pipeline.
// Intreceptors execute in registration order (first = outermost wrapper).
// Stateless after construction - safe to call from multiple threads.

template<typename TRequest, typename TResponse>
class UseCasePipeline {

    public:

        using InterceptorPtr = std::shared_ptr<IInterceptor<TRequest, TResponse>>;

        using UseCasePtr = std::shared_ptr<IUseCase<TRequest, TResponse>>;

        explicit UseCasePipeline(UseCasePtr useCase) : _useCase(std::move(usecase)) {}

        UseCasePipeline& addInterceptor(InterceptorPtr interceptor) {

            _interceptors.push_back(std::move(interceptor));
            return *this;
        }

        UseCaseResult<TResponse> execute(const ExecutionContext& ctx, const TRequest& request) {

            return buildChain(ctx, request, 0)();
        }

    private:

        std::vector<InterceptorPtr> _interceptors;
        UseCasePtr                  _useCase;

        // Builds a recursive closure chain. Each closure holds a shared_ptr copy
        // of the interceptor - no dangling references across the chain.
        std::function<UseCaseResult<TResponse>()> buildChain(const ExecutionContext& ctx,
                                                             const TRequest&         request,
                                                             std::size_t             index) const {

            if (index == _interceptors.size()) {

                return [this, &ctx, &request]() { return _useCase->execute(ctx, request); };
            }

            auto interceptor = _interceptors[index];  // shared_ptr copy
            auto next        = buildChain(ctx, request, index + 1);

            return [interceptor, &ctx, &request, next]() mutable {
                return interceptor->intercept(ctx, request, next);
            };
        }
};