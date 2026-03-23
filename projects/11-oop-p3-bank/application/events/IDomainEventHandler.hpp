#pragma once

#include <type_traits>

#include "application/events/IDomainEvent.hpp"

// Handles a specific domain event type.
// Implementations:
//		- Write OutboxEntries for integration events
//		- Update read models / projections
//		- Trigger other in-process side effects
//
// What handlers must Not do:
//		- Call external services directly (use outbox)
//		- Open new DB transactions (already inside one)

template<typename TEvent>
class IDomainEventHandler {

        static_assert(std::is_base_of<IDomainEvent, TEvent>::value,
                      "TEvent must inherit IDomainEvent");

    public:

        virtual void handle(const TEvent& event) = 0;

        virtual ~IDomainEventHandler() = default;
};