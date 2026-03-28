#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

#include "application/tasks/ITaskQueue.hpp"

// Single consumer thread - tasks processed sequentially.
// Tasks are lost on process crash - acceptable for dev.
// Swap with RabbitMqTaskQueue

struct QueuedTask {

        std::string type;
        std::string payload;
};

class InMemoryTaskQueue : public ITaskQueue {

    public:

        ~InMemoryTaskQueue() override {
            if (_running)
                stop();
        }

        void enqueue(const ITask& task) override;

        void registerHandler(const std::string& type, TaskHandler h) override;

        void start() override;

        void stop() override;

    private:

        std::queue<QueuedTask>                       _queue;
        std::unordered_map<std::string, TaskHandler> _handlers;
        std::mutex                                   _mutex;
        std::condition_variable                      _cv;
        std::thread                                  _worker;
        std::atomic<bool>                            _running{false};

        void consumeLoop();
        void dispatch(const QueuedTask& task);
};