#pragma once

#include <optional>
#include <string>

#include "application/abstractions/CallerIdentity.hpp"

// Session management port.
// createSession - called by LoginUseCase on successful auth.
// resolveSession - called by the controller to build ExecutionContext.
// Implementation: JWT, server-side session store.

class ISessionService {

    public:

        // TODO: replace with existing CallerIdentity
        virtual std::string createSession(const std::string& userId,
                                          const std::string& roleName,
                                          int                permissions) = 0;

        virtual std::optional<CallerIdentity> resolveSession(const std::string& token) = 0;

        virtual void revokeSession(const std::string& token) = 0;

        virtual ~ISessionService() = default;
};