#pragma once

#include <optional>
#include <string>

#include "domain/repositories/IUserRepository.hpp"

#include "application/common/UseCaseResult.hpp"
#include "application/dto/LoginResponse.hpp"
#include "application/ports/IPasswordHasher.hpp"

class LoginUseCase {
    private:

        IUserRepository& _userRepo;

        IPasswordHasher& _passwordHasher;

    public:

        LoginUseCase(IUserRepository& userRepo, IPasswordHasher& passwordHasher)
            : _userRepo(userRepo), _passwordHasher(passwordHasher) {}

        UseCaseResult<LoginResponse> execute(const std::string& username,
                                             const std::string& password) {

            auto user = _userRepo.findByUsername(username);

            if (!user.has_value()) {
                return UseCaseResult<LoginResponse>::failure("Invalid username or password");
            }

            if (!_passwordHasher.verify(password, user->getPasswordHash())) {
                return UseCaseResult<LoginResponse>::failure("Invalid username or password");
            }

            LoginResponse response(user->getUsername(), user->getRole());

            return UseCaseResult<LoginResponse>::success(std::move(response));
        }
};