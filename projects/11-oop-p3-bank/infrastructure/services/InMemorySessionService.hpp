#pragma once

#include <mutex>
#include <optional>
#include <unordered_map>

#include "application/services/ISessionService.hpp"

#include "infrastructure/services/UuidGenerator.hpp"

// Stores sessions in memory - lost on process restart.
// Swap with JwtSessionService (stateless) or RedisSessionService (persistent).

class InMemorySessionService : public ISessionService {

    public:

        std::string createSession(const std::string& userId,
                                  const std::string& roleName,
                                  int                permissions) override;

        std::optional<CallerIdentity> resolveSession(const std::string& token) override;

        void revokeSession(const std::string& token) override;

    private:

        struct SessionData {

                std::string userId;
                std::string username;
                std::string roleName;
                int         permissions;
        };

        std::unordered_map<std::string, SessionData> _sessions;
        std::mutex                                   _mutex;
        UuidGenerator                                _uuidGen;
};