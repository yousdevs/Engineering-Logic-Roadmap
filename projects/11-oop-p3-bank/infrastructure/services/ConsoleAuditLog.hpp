#pragma once

#include <ctime>
#include <iomanip>
#include <iostream>

#include "application/audit/IAuditLog.hpp"

// Writes audit entries to stdout - for development.
// swap with SqliteAuditLog

class ConsoleAuditLog : public IAuditLog {

    public:

        void record(const AuditEntry& e) override {

            std::tm* tm = std::localtime(&e.occurredAt);

            std::cout << "[AUDIT]" << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << " | "
                      << outcomeStr(e.outcome) << " | " << e.operation << " | caller=" << e.callerId
                      << " | ip=" << e.ipAddress << " | req=" << e.requestId;

            if (!e.detail.empty())
                std::cout << " | detail=" << e.detail;

            std::cout << '\n';
        }

    private:

        static const char* outcomeStr(AuditOutcome o) {

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
};