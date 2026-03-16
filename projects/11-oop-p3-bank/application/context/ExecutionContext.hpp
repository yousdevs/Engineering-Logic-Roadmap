#pragma once

#include <string>

class ExecutionContext {

    private:

        std::string _username;
        std::string _role;

    public:

        ExecutionContext(std::string username, std::string role)
            : _username(std::move(username)), _role(std::move(role)) {}

        const std::string& getUsername() const {
            return _username;
        }

        const std::string& getRole() const {
            return _role;
        }
};