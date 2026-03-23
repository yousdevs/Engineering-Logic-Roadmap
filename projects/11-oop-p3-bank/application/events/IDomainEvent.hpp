#pragma once

#include <ctime>
#include <string>

// Base for all in-proccess domain events.
// Raised after the use case completes - handlers run inside the same transaction.
// eventId is used as the OutboxEntry.id - enables consumer-side idempotency.

class IDomainEvent {

    public:

        virtual std::string eventType() const = 0;

        virtual std::string eventId() const = 0;

        virtual std::time_t occurredAt() const = 0;

        virtual ~IDomainEvent() = default;
};