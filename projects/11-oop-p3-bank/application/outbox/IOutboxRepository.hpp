#pragma once

#include <string>
#include <vector>

#include "application/outbox/OutboxEntry.hpp"

// Written by event handlers inside the active transaction.
// Read by OutboxPoller on a background thread.

// TODO: Add safe claiming/locking to prevent multiple workers processing the same entries

class IOutboxRepository {

    public:

        // Called inside the active transaction - atomic with domain saves.
        virtual void save(const OutboxEntry& entry) = 0;

        // Returns unprocessed entries oldest-first, up to limit.
        virtual std::vector<OutboxEntry> findPending(int limit = 50) = 0;

        virtual void markProcessed(const std::string& entryId) = 0;

        virtual void incrementAttempts(const std::string& entryId) = 0;

        // Returns entries that have exceeded maxAttempts - needs investigation.
        virtual std::vector<OutboxEntry> findDeadLetters(int maxAttempts = 5) = 0;

        virtual ~IOutboxRepository() = default;
};