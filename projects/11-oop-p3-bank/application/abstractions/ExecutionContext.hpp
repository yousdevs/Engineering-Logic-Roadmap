#pragma once

#include <ctime>
#include <optional>
#include <string>

#include "application/abstractions/CallerIdentity.hpp"
#include "application/abstractions/CallerType.hpp"

// Request context injected into every use case via the pipeline.
// identity is absent for public/anonymous calls.
// Created by the controller - never by a use case.

struct ExecutionContext {

        std::optional<CallerIdentity> identity;   // absent = anonymous
        std::string                   requestId;  // UUID - log correlation
        std::string                   ipAddress;
        std::time_t                   requestedAt;
        CallerType                    callerType;

        bool isAuthenticated() const {
            return identity.has_value();
        }

        bool can(int permission) const {
            return isAuthenticated() && identity->can(permission);
        }

        std::string callerId() const {
            return isAuthenticated() ? identity->userId : "anonymous";
        }

        // Static factories

        static ExecutionContext authenticated(const CallerIdentity& id,
                                              const std::string&    requestId,
                                              const std::string&    ipAddress,
                                              CallerType callerType = CallerType::WebClient) {

            return {id, requestId, ipAddress, std::time(nullptr), callerType};
        }

        static ExecutionContext anonymous(const std::string& requestId,
                                          const std::string& ipAddress) {

            return {std::nullopt, requestId, ipAddress, std::time(nullptr), CallerType::PublicApi};
        }
};