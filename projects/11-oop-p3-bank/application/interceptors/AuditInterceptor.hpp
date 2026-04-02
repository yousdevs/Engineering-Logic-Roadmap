#pragma once

#include <ctime>
#include <memory>
#include <string>

#include "application/abstractions/IInterceptor.hpp"
#include "application/audit/IAuditLog.hpp"

// Applied when UseCaseMetadata.audited = true.
// Records Started before next(), then Succeeded or Failed after.
// Wraps auth and transaction interceptors - sees the final outcome.

template<typename TRequest, typename TResponse>
class AuditInterceptor : public IInterceptor<TRequest, TResponse> {

    public:

        AuditInterceptor(std::string useCaseName, std::shared_ptr<IAuditLog> auditLog)
            : _name(std::move(useCaseName)), _auditLog(std::move(auditLog)) {}

        UseCaseResult<TResponse> intercept(
            const ExecutionContext&                            ctx,
            const TRequest&                                    request,
            typename IInterceptor<TRequest, TResponse>::NextFn next) override {

            _auditLog->record({ctx.requestId,
                               ctx.callerId(),
                               _name,
                               AuditOutcome::Started,
                               "",
                               ctx.ipAddress,
                               std::time(nullptr)});

            auto result = next();

            _auditLog->record({ctx.requestId,
                               ctx.callerId(),
                               _name,
                               result.success ? AuditOutcome::Succeeded : AuditOutcome::Failed,
                               result.success ? "" : result.error->message,
                               ctx.ipAddress,
                               std::time(nullptr)});

            return result;
        }

    private:

        std::string                _name;
        std::shared_ptr<IAuditLog> _auditLog;
};