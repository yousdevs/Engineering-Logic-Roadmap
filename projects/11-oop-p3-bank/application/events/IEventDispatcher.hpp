#pragma once

#include <functional>
#include <string>

#include "application/events/IDomainEvent.hpp"

// In-process domain event dispatcher.
// Use cases call dispatch() inside the active transaction.
// Handlers write OutboxEntries - they never publish externally.
// The OutboxPoller handles external delivery after the commit.

class IEventDispatcher {

    public:

        using HandlerFn = std::function<void(const IDomainEvent&)>;

        // Called once at startup - registers handlers by event type string.
        virtual void registerHandler(const std::string& eventType, HandlerFn handler) = 0;

        // Calls all handlers registered for event.eventType() synchronously.
        virtual void dispatch(const IDomainEvent& event) = 0;

        virtual ~IEventDispatcher() = default;
};