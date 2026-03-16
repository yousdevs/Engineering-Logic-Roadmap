#pragma once

#include <optional>
#include <string>

#include "domain/repositories/IUserRepository.hpp"

#include "application/common/UseCaseResult.hpp"
#include "application/dto/LoginRequest.hpp"
#include "application/dto/LoginResponse.hpp"
#include "application/ports/IPasswordHasher.hpp"

class LoginUseCase {
    private:

        IUserRepository& _userRepo;

        IPasswordHasher& _passwordHasher;

    public:

        LoginUseCase(IUserRepository& userRepo, IPasswordHasher& passwordHasher)
            : _userRepo(userRepo), _passwordHasher(passwordHasher) {}

        UseCaseResult<LoginResponse> execute(const LoginRequest& request) {

            auto user = _userRepo.findByUsername(request.username);

            if (!user.has_value()) {
                return UseCaseResult<LoginResponse>::failure("Invalid username or password");
            }

            if (!_passwordHasher.verify(request.password, user->getPasswordHash())) {
                return UseCaseResult<LoginResponse>::failure("Invalid username or password");
            }

            LoginResponse response(user->getUsername(), user->getRole());

            return UseCaseResult<LoginResponse>::success(std::move(response));
        }
};