#include "infrastructure/services/InMemoryRealtimePublisher.hpp"

void InMemoryRealtimePublisher::publish(const std::string& channel, const std::string& payload) {

    std::vector<MessageHandler> handlers;

    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto                        it = _handlers.find(channel);
        if (it != _handlers.end())
            handlers = it->second;  // copy under lock
    }
    for (auto& h : handlers) {

        try {

            h(payload);
        } catch (...) {
            // isolate bad handlers
        }
    }
}

void InMemoryRealtimePublisher::subscribe(const std::string& channel, MessageHandler handler) {

    std::lock_guard<std::mutex> lock(_mutex);
    _handlers[channel].push_back(std::move(handler));
}

void InMemoryRealtimePublisher::unsubscribe(const std::string& channel) {

    std::lock_guard<std::mutex> lock(_mutex);
    _handlers.erase(channel);
}