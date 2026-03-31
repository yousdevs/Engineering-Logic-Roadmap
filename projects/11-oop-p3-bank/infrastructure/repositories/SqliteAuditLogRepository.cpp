#include "infrastructure/repositories/SqliteAuditLogRepository.hpp"

#include <iostream>

static std::string outcomeStr(AuditOutcome o) {

    switch (o) {

        case AuditOutcome::Started:
            return "STARTED";
        case AuditOutcome::Succeeded:
            return "SUCCEEDED";
        case AuditOutcome::Failed:
            return "FAILED";
    }

    return "UNKNOWN";
}

void SqliteAuditLogRepository::record(const AuditEntry& e) {

    // Fire-and-forget - if the audit write fails we log to stderr
    // but never propagate the error back to the use case.
    try {

        _conn->exec(

            "INSERT INTO audit_log (request_id, caller_id, operation, "
            " outcome, detail, ip_address, occurred_at) "
            "VALUES (?, ?, ?, ?, ?, ?, ?);",
            {e.requestId,
             e.callerId,
             e.operation,
             outcomeStr(e.outcome),
             e.detail,
             e.ipAddress,
             std::to_string(static_cast<long long>(e.occurredAt))});
    } catch (const std::exception& ex) {

        // Audit must never crash the application.
        std::cerr << "[AUDIT ERROR] " << ex.what() << "\n";
    }
}