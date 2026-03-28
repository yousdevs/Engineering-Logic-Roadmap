#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include "application/outbox/IOutboxPoller.hpp"
#include "application/outbox/IOutboxRepository.hpp"
#include "application/tasks/ITaskQueue.hpp"

// Reads pending OutboxEntries and enqueues them to ITaskQueue.
// Marks processed on success; increments attempts on failure.
// Entries exceeding maxAttempts become dead letters (skipped + alertable).
// Polls every pollingIntervalMs - not a tight loop.

class OutboxPoller : public IOutboxPoller {

    public:

        OutboxPoller(std::shared_ptr<IOutboxRepository> outboxRepo,
                     std::shared_ptr<ITaskQueue>        taskQueue,
                     int                                pollingIntervalMs = 1000,
                     int                                batchSize         = 50,
                     int                                maxAttempts       = 5)
            : _outboxRepo(std::move(outboxRepo))
            , _taskQueue(std::move(taskQueue))
            , _pollingIntervalMs(pollingIntervalMs)
            , _batchSize(batchSize)
            , _maxAttempts(maxAttempts)
            , _running(false) {}

        ~OutboxPoller() override {
            if (_running)
                stop();
        }

        void start() override;

        void stop() override;

    private:

        std::shared_ptr<IOutboxRepository> _outboxRepo;
        std::shared_ptr<ITaskQueue>        _taskQueue;
        int                                _pollingIntervalMs;
        int                                _batchSize;
        int                                _maxAttempts;
        std::atomic<bool>                  _running;
        std::thread                        _thread;

        void pollLoop();
        void processBatch();
};