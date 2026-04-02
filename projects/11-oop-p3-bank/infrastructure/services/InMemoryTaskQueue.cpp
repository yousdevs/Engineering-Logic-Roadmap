#include "infrastructure/services/InMemoryTaskQueue.hpp"

void InMemoryTaskQueue::enqueue(const ITask& task) {

    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push({task.taskType(), task.serialize()});
    }
    _cv.notify_one();
}

void InMemoryTaskQueue::registerHandler(const std::string& type, TaskHandler h) {

    _handlers[type] = std::move(h);  // startup only - no lock needed
}

void InMemoryTaskQueue::start() {

    _running = true;
    _worker  = std::thread(&InMemoryTaskQueue::consumeLoop, this);
}

void InMemoryTaskQueue::stop() {

    _running = false;
    _cv.notify_all();
    if (_worker.joinable())
        _worker.join();
}

void InMemoryTaskQueue::consumeLoop() {

    while (_running) {

        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] { return !_queue.empty() || !_running; });

        while (!_queue.empty()) {

            auto task = _queue.front();
            _queue.pop();
            lock.unlock();
            dispatch(task);
            lock.lock();
        }
    }
}

void InMemoryTaskQueue::dispatch(const QueuedTask& task) {

    auto it = _handlers.find(task.type);
    if (it == _handlers.end())
        return;  // unregistered type - log in prod

    try {
        it->second(task.payload);
    } catch (...) {
        // TODO:log faiilure
    }
}