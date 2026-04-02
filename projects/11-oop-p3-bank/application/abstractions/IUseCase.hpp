#pragma once
#include <string>
#include <type_traits>
#include <vector>

#include "application/abstractions/ExecutionContext.hpp"
#include "application/abstractions/UseCaseMetadata.hpp"
#include "application/abstractions/UseCaseResult.hpp"

// Marker base types

struct ValidationError {

        std::string field;
        std::string message;
};

struct UseCaseRequest {

        // Override to declare field-level validation rules.
        // ValidationIntreceptor calls this before the use case runs.
        virtual std::vector<ValidationError> validate() const {
            return {};
        }
        virtual ~UseCaseRequest() = default;
};

struct UseCaseResponse {

        virtual ~UseCaseResponse() = default;
};

// IUseCase
// Every use case implements this interface.
// metadata() is the NestJS decorator equivalent - PipeLineBuilder reads it.
// Use cases: never check auth, never open transactions, never write audit logs.

template<typename TRequest, typename TResponse>
class IUseCase {

        static_assert(std::is_base_of<UseCaseRequest, TRequest>::value,
                      "TRequest must inherit UseCaseRequest");

        static_assert(std::is_base_of<UseCaseResponse, TResponse>::value,
                      "TResponse must inherit UseCaseResponse");

    public:

        virtual UseCaseMetadata metadata() const = 0;

        virtual UseCaseResult<TResponse> execute(const ExecutionContext&, const TRequest&) = 0;

        virtual ~IUseCase() = default;
};

// Void specialization - for use cases that return no data.
template<typename TRequest>
class IUseCase<TRequest, void> {

        static_assert(std::is_base_of<UseCaseRequest, TRequest>::value,
                      "TRequest must inherit UseCaseRequest");

    public:

        virtual UseCaseMetadata metadata() const = 0;

        virtual UseCaseResult<void> execute(const ExecutionContext&, const TRequest&) = 0;

        virtual ~IUseCase() = default;
};