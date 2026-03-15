#pragma once

#include <string>
#include <optional>

#include "AuthenticatedUser.hpp"

struct LoginResult {
	
	bool success;

    std::string message;
        
	std::optional<AuthenticatedUser> user;
};