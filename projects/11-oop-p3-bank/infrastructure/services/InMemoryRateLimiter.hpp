#pragma once

#include <ctime>
#include <mutex>
#include <unordered_map>

#include "application/services/IRateLimiter.hpp"

// Single-node rate limiter - counters reset after windowSeconds.
// Swap with RedisRateLimiter for multi-instance deployments.
// Thread-safe: mutex protects the counter map.

class InMemoryRateLimiter : public IRateLimiter {

    public:

        explicit InMemoryRateLimiter(int maxRequests = 10, int windowSeconds = 60)
            : _maxRequests(maxRequests), _windowSeconds(windowSeconds) {}

        bool isLimited(const std::string& key) override;

        void increment(const std::string& key) override;

        void reset(const std::string& key) override;

    private:

        struct Entry {
                int         count       = 0;
                std::time_t windowStart = 0;
        };

        int                                    _maxRequests;
        int                                    _windowSeconds;
        std::unordered_map<std::string, Entry> _counters;
        std::mutex                             _mutex;

        void evictIfExpired(Entry& entry);
};