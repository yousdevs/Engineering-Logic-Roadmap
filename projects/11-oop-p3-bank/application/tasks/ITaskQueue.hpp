#pragma once

#include <functional>
#include <string>

#include "application/tasks/ITask.hpp"

// Background task broker port.
// enqueue() is non-blocking - caller does not wait for task completion.
// Implementations: InMemoryTaskQueue (dev), RabbitMqTaskQueue.
// Swap implementation in CompositionRoot - zero application layer changes.

class ITaskQueue {

    public:

        using TaskHandler = std::function<void(const std::string& payload)>;

        virtual void enqueue(const ITask& task) = 0;

        // Registers a handler by task type string - called once at startup.
        virtual void registerHandler(const std::string& taskType, TaskHandler handler) = 0;

        virtual void start() = 0;  // starts background consumer thread

        virtual void stop() = 0;   // stops gracefully, waits for current task

        virtual ~ITaskQueue() = default;
};