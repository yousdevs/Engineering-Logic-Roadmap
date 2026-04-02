#pragma once

#include <ctime>
#include <optional>
#include <string>

// A serialized domain event pending external delivery.
// Written in the same DB transaction as domain entity saves - atomic.
// Read and published by OutboxPoller on a background thread.
// processedAt absent = pending. attempts >= maxAttempts = dead letter.
// Consumers must be idempotent - at-least-once delivery is guaranteed.

// TODO: Add status, locking, error tracking, and event versioning for robust retries and
// concurrency

struct OutboxEntry {

        std::string                id;           // == IDomainEvent.eventId() (for idempotoncy
        std::string                eventType;
        std::string                payload;      // JSON
        std::time_t                occurredAt;
        std::optional<std::time_t> processedAt;  // absent = pending
        int                        attempts = 0;
};