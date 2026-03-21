#pragma once
#include <optional>
#include <stdexcept>

#include "application/abstractions/AppError.hpp"

// Universal result wrapper - use cases never throw across boundaries.
// Caller always handles both success and failure paths explicitly.

template<typename TResponse>
struct UseCaseResult {

        bool                     success;
        std::optional<TResponse> data;
        std::optional<AppError>  error;

        static UseCaseResult ok(TResponse response) {
            return {true, std::move(response), std::nullopt};
        }

        static UseCaseResult fail(AppError err) {
            return {false, std::nullopt, std::move(err)};
        }

        const TResponse& unwrap() const {
            if (!success)
                throw std::logic_error("unwrap() on failed result: " + error->message);
            return data.value();
        }
};

// Void specialization - for use cases that return no data.
template<>
struct UseCaseResult<void> {
        bool                    success;
        std::optional<AppError> error;

        static UseCaseResult ok() {
            return {true, std::nullopt};
        }

        static UseCaseResult fail(AppError e) {
            return {false, std::move(e)};
        }
};