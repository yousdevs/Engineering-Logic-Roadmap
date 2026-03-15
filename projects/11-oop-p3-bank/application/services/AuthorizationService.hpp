#pragma once

#include <string>

#include <../../domain/security/Roles.hpp>

class AuthorizationService {

	public:

	static bool hasPermission(const std::string& role, int permission) {

		return (permissionFromRole(role) & permission) == permission; 
	}
};