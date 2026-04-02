#pragma once

#include <string>

#include "application/abstractions/CallerType.hpp"

// Declarative use case configutation - the C++ equivelent of NestJS decorators.
// @UseGuards(AuthGuard)  -> requiresAuth = true
// @Roles(permission::X)  -> permission = X
// @UseIntreceptors(...)  -> transactional / audited / rateLimited flags
//
// PipelineBuilder reads this and assembles only the intreceptors needed.
// Use cases declare their own metadata via metadata() override.

struct UseCaseMetadata {

        std::string  name;
        bool         requiresAuth  = true;
        int          permission    = 0;
        bool         transactional = true;
        bool         audited       = true;
        bool         rateLimited   = false;
        CallerPolicy callerPolicy  = CallerPolicy::AnyAuthenticated;

        // Fluent builder

        static UseCaseMetadata create(const std::string& name) {

            UseCaseMetadata m;
            m.name = name;
            return m;
        }

        UseCaseMetadata& withPermission(int perm) {

            permission = perm;
            return *this;
        }

        UseCaseMetadata& asPublic() {

            requiresAuth = false;
            permission   = 0;
            callerPolicy = CallerPolicy::AnyCallerType;
            return *this;
        }

        UseCaseMetadata& readOnly() {

            transactional = false;
            return *this;
        }

        UseCaseMetadata& withoutAudit() {

            audited = false;
            return *this;
        }

        UseCaseMetadata& withRateLimit() {

            rateLimited = true;
            return *this;
        }
};