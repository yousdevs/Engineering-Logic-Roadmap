#pragma once

// Background service that reads pending OutboxEntries and delivers them.
// On each tick: findPending -> enqueue to ITaskQueue -> markProcessed.
// stop() signals graceful shutdown and waits for the current cycle to finish.

// TODO: Ensure safe processing (claim before process, handle retries, avoid duplicate delivery)

class IOutboxPoller {

    public:

        virtual void start() = 0;

        virtual void stop() = 0;

        virtual ~IOutboxPoller() = default;
};