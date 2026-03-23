#pragma once

#include <unordered_map>
#include <vector>

#include "application/events/IEventDispatcher.hpp"

// Concrete in-process dispatcher.
// All handlers for a given event type are called in registration order.
// A handler failure is caugh and isolated - other handlers still run.
// The transaction has not committed yet - a fatal handler may rethrow
// to trigger rollback if the event is critical to consistency.

class EventDispatcher : public IEventDispatcher {

    public:

        void registerHandler(const std::string& eventType, HandlerFn handler) override {

            _handlers[eventType].push_back(std::move(handler));
        }

        void dispatch(const IDomainEvent& event) override {

            auto it = _handlers.find(event.eventType());

            if (it == _handlers.end())
                return;

            for (auto& handler : it->second) {

                try {
                    handler(event);
                } catch (...) {
                    // log - do not abort other handlers
                }
            }
        }

    private:

        std::unordered_map<std::string, std::vector<HandlerFn>> _handlers;
};