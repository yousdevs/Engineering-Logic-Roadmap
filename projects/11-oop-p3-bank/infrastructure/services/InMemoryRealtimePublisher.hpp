#pragma once

#include <mutex>
#include <unordered_map>
#include <vector>

#include "application/services/IRealtimePublisher.hpp"

// Single-process publisher - handlers called synchronously on publish thread.
// Swap with RedisRealtimePublisher for multi-instance fan-out.
// Handlers are copied under lock then called outside lock - prevents deadlock.

class InMemoryRealtimePublisher : public IRealtimePublisher {

    public:

        void publish(const std::string& channel, const std::string& payload) override;

        void subscribe(const std::string& channel, MessageHandler handler) override;

        void unsubscribe(const std::string& channel) override;

    private:

        std::unordered_map<std::string, std::vector<MessageHandler>> _handlers;
        std::mutex                                                   _mutex;
};