#pragma once

#include <string>
#include <utility>

class LoginResponse {

    private:

        std::string _username;
        std::string _role;

    public:

        LoginResponse(std::string username, std::string role)
            : _username(std::move(username)), _role(std::move(role)) {}

        const std::string& getUsername() const {
            return _username;
        }

        const std::string& getRole() const {  // TODO use Domain Role
            return _role;
        }
};