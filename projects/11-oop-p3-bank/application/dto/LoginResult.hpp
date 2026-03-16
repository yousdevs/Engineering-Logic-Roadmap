#pragma once

#include "AuthenticatedUser.hpp"

#include <optional>
#include <string>

struct LoginResult {

        bool success;

        std::string message;

        std::optional<AuthenticatedUser> user;
};