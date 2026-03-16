#pragma once

#include <optional>
#include <string>

#include "domain/repositories/IUserRepository.hpp"

#include "application/dto/LoginResult.hpp"
#include "application/ports/IPasswordHasher.hpp"

class LoginUseCase {
    private:

        IUserRepository& _userRepo;

        IPasswordHasher& _passwordHasher;

    public:

        LoginUseCase(IUserRepository& userRepo, IPasswordHasher& passwordHasher)
            : _userRepo(userRepo), _passwordHasher(passwordHasher) {}

        LoginResult execute(const std::string& username, const std::string& password) {

            auto user = _userRepo.findByUsername(username);

            if (!user.has_value()) {
                return LoginResult{false, "Invalid username or password", std::nullopt};
            }

            if (!_passwordHasher.verify(password, user->getPasswordHash())) {
                return LoginResult{false, "Invalid username or password", std::nullopt};
            }

            return LoginResult{
                true, "Login successful", AuthenticatedUser{user->getUsername(), user->getRole()}};
        }
};