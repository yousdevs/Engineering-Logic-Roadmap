#pragma once

#include <memory>

#include "domain/ports/IUnitOfWork.hpp"

#include "application/abstractions/AppError.hpp"
#include "application/abstractions/IInterceptor.hpp"

// Applied when UseCaseMetadata.transactional = true.
// Wraps the use case in a Unit of Work.
// Commits on success - this atomically saves domain entities
// And outbox entries written during the same call.
// Rolls back on failure or exception.

// TODO: Improve transaction safety (handle commit failures and avoid swallowing exceptions).

template<typename TRequest, typename TResponse>
class TransactionInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        explicit TransactionInterceptor(std::shared_ptr<IUnitOfWork> uow) : _uow(std::move(uow)) {}

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            _uow->begin();

            try {

                auto result = next();

                result.success ? _uow->commit() : _uow->rollback();
                return result;

            } catch (const std::exception& ex) {

                _uow->rollback();

                return UseCaseResult<TResponse>::fail(AppError::internal(ex.what()));
            }
        }

    private:

        std::shared_ptr<IUnitOfWork> _uow;
};