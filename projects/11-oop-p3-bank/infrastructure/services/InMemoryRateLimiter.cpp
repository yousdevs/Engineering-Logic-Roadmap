#include "infrastructure/services/InMemoryRateLimiter.hpp"

void InMemoryRateLimiter::evictIfExpired(Entry& entry) {

    const std::time_t now = std::time(nullptr);
    if (now - entry.windowStart >= _windowSeconds) {

        entry.count       = 0;
        entry.windowStart = now;
    }
}

bool InMemoryRateLimiter::isLimited(const std::string& key) {

    std::lock_guard<std::mutex> lock(_mutex);
    auto&                       entry = _counters[key];
    evictIfExpired(entry);
    return entry.count >= _maxRequests;
}

void InMemoryRateLimiter::increment(const std::string& key) {

    std::lock_guard<std::mutex> lock(_mutex);
    auto&                       entry = _counters[key];
    if (entry.windowStart == 0)
        entry.windowStart = std::time(nullptr);
    evictIfExpired(entry);
    ++entry.count;
}

void InMemoryRateLimiter::reset(const std::string& key) {

    std::lock_guard<std::mutex> lock(_mutex);
    _counters.erase(key);
}