#include "infrastructure/services/InMemorySessionService.hpp"

std::string InMemorySessionService::createSession(const std::string& userId,
                                                  const std::string& roleName,
                                                  int                permissions) {

    const std::string           token = _uuidGen.generate();
    std::lock_guard<std::mutex> lock(_mutex);
    _sessions[token] = {userId, "", roleName, permissions};

    return token;
}

std::optional<CallerIdentity> InMemorySessionService::resolveSession(const std::string& token) {

    std::lock_guard<std::mutex> lock(_mutex);
    auto                        it = _sessions.find(token);
    if (it == _sessions.end())
        return std::nullopt;

    const auto& s = it->second;
    return CallerIdentity{s.userId, s.username, s.roleName, s.permissions};
}

void InMemorySessionService::revokeSession(const std::string& token) {

    std::lock_guard<std::mutex> lock(_mutex);
    _sessions.erase(token);
}