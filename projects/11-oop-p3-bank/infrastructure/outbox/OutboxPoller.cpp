#include "infrastructure/outbox/OutboxPoller.hpp"

// Proxy task - carries raw type + payload from the outbox entry.
// ITaskQueue routes it to the registered handler by type string.
struct OutboxProxyTask : public ITask {

        std::string _type, _payload;

        OutboxProxyTask(std::string t, std::string p)
            : _type(std::move(t)), _payload(std::move(p)) {}

        std::string taskType() const override {
            return _type;
        }
        std::string serialize() const override {
            return _payload;
        }
};

void OutboxPoller::start() {

    _running = true;
    _thread  = std::thread(&OutboxPoller::pollLoop, this);
}

void OutboxPoller::stop() {

    _running = false;
    if (_thread.joinable())
        _thread.join();
}

void OutboxPoller::pollLoop() {

    while (_running) {

        try {
            processBatch();
        } catch (...) {
            // Log - never crash the background thread
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(_pollingIntervalMs));
    }
}

void OutboxPoller::processBatch() {

    for (const auto& entry : _outboxRepo->findPending(_batchSize)) {

        if (entry.attempts >= _maxAttempts)
            continue;  // dead letter - alert

        try {

            _taskQueue->enqueue(OutboxProxyTask{entry.eventType, entry.payload});

            _outboxRepo->markProcessed(entry.id);
        } catch (...) {

            // Delivery failed - retry on next cycle.
            // Idempotency contract: consumers handle dublicate delivery.
            _outboxRepo->incrementAttempts(entry.id);
        }
    }
}