#pragma once

#include <string>

// Rate Limiting port.
// Key convention: "{ipAddress}:{operationName}"
// Implementations: InMemoryRateLimiter (single node),
//					RedisRateLimiter    (multi-node - shared counters).
// TODO: atomicity

class IRateLimiter {

    public:

        virtual bool isLimited(const std::string& key) = 0;

        virtual void increment(const std::string& key) = 0;

        virtual void reset(const std::string& key) = 0;

        virtual ~IRateLimiter() = default;
};