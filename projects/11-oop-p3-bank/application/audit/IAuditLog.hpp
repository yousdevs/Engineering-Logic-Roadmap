#pragma once

#include <ctime>
#include <string>

enum class AuditOutcome { Started, Succeeded, Failed };

struct AuditEntry {

        std::string  requestId;
        std::string  callerId;  // userId or "anonymous"
        std::string  operation;
        AuditOutcome outcome;
        std::string  detail;  // error message on failure, empty otherwise
        std::string  ipAddress;
        std::time_t  occurredAt;
};

// Append-only audit trail - never updated or deleted ( compliance requirements).
class IAuditLog {

    public:

        virtual void record(const AuditEntry& entry) = 0;

        virtual ~IAuditLog() = default;
};