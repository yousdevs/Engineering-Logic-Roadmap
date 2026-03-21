#pragma once
#include <string>

// Typed application error - carried by UseCaseResult on failure
// ErrorCode maps to HTTP status at the presentation layer.

enum class ErrorCode {
    ValidationFailed,
    Unauthorized,
    Forbidden,
    NotFound,
    Conflict,
    BusinessRuleViolation,
    InternalError
};

struct AppError {

        ErrorCode   code;
        std::string message;
        std::string field;  // optional - identifies the offending field

        static AppError validation(const std::string& msg, const std::string& field = "") {
            return {ErrorCode::ValidationFailed, msg, field};
        }

        static AppError unauthorized(const std::string& msg) {
            return {ErrorCode::Unauthorized, msg, ""};
        }

        static AppError forbidden(const std::string& msg) {
            return {ErrorCode::Forbidden, msg, ""};
        }

        static AppError notFound(const std::string& msg) {
            return {ErrorCode::NotFound, msg, ""};
        }

        static AppError conflict(const std::string& msg) {
            return {ErrorCode::Conflict, msg, ""};
        }

        static AppError businessRule(const std::string& msg) {
            return {ErrorCode::BusinessRuleViolation, msg, ""};
        }

        static AppError internal(const std::string& msg) {
            return {ErrorCode::InternalError, msg, ""};
        }
};