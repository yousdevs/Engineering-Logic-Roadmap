#pragma once

#include <string>

// Serializable unit of background work.
// Tasks carry DATA, not closures - this is what makes them broker-compatible.
// std::function<void()> cannot cross a process boundary; ITask can.
// Consumers must be idempotent - at-least-once delivery is guaranteed.

class ITask {

    public:

        virtual std::string taskType() const = 0;   // registry key for deserialization

        virtual std::string serialize() const = 0;  // JSON payload

        virtual ~ITask() = default;
};