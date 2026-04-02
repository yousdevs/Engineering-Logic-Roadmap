#pragma once

#include <functional>
#include <string>

// Real-time channel publish/subscribe port.
// Channel naming: "account.{id}", "rates.{from}.{to}", "system.alerts"
// Implementations: InMemoryRealtimePublisher (dev, single process),
//					RedisRealtimePublisher    (prod, multi-instance fan-out).

// TODO: multiple handlers / error handling / retries / structured payload

class IRealtimePublisher {

    public:

        using MessageHandler = std::function<void(const std::string& payload)>;

        virtual void publish(const std::string& channel, const std::string& payload) = 0;

        virtual void subscribe(const std::string& channel, MessageHandler handler) = 0;

        virtual void unsubscribe(const std::string& channel) = 0;

        virtual ~IRealtimePublisher() = default;
};