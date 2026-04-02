#pragma once

#include <memory>
#include <string>

#include "domain/ports/IPasswordHasher.hpp"
#include "domain/repositories/IUserRepository.hpp"

#include "application/abstractions/IUseCase.hpp"
#include "application/services/ISessionService.hpp"

struct LoginRequest : UseCaseRequest {

        std::string username;
        std::string password;

        std::vector<ValidationError> validate() const override {

            std::vector<ValidationError> errors;

            if (username.empty())
                errors.push_back({"username", "Required."});
            if (password.empty())
                errors.push_back({"password", "Required."});

            return errors;
        }
};

struct LoginResponse : UseCaseResponse {

        std::string userId;
        std::string username;
        std::string role;
        std::string sessionToken;

        LoginResponse(std::string userId,
                      std::string username,
                      std::string role,
                      std::string sessionToken)
            : userId(std::move(userId))
            , username(std::move(username))
            , role(std::move(role))
            , sessionToken(std::move(sessionToken)) {}
};

// Public, rate-limited, audited, read-only.
// No domain User in the context before this runs - creates the session.
// Error messages are intentionally vague - prevents user enumeration.

class LoginUseCase : public IUseCase<LoginRequest, LoginResponse> {

    public:

        LoginUseCase(std::shared_ptr<IUserRepository> userRepo,
                     std::shared_ptr<IPasswordHasher> hasher,
                     std::shared_ptr<ISessionService> sessionService)
            : _userRepo(std::move(userRepo))
            , _hasher(std::move(hasher))
            , _sessionService(std::move(sessionService)) {}

        UseCaseMetadata metadata() const override {

            return UseCaseMetadata::create("Login").asPublic().readOnly().withRateLimit();
        }

        UseCaseResult<LoginResponse> execute(const ExecutionContext& ctx,
                                             const LoginRequest&     request) override {

            auto user = _userRepo->findByUsername(request.username);

            if (!user.has_value() || user->isDeleted()
                || !_hasher->verify(request.password, user->passwordHash())) {

                return UseCaseResult<LoginResponse>::fail(
                    AppError::unauthorized("Invalid username or password."));
            }

            auto token = _sessionService->createSession(
                user->id().value(), user->role().name(), user->role().permissions());

            return UseCaseResult<LoginResponse>::ok(
                LoginResponse{user->id().value(), user->username(), user->role().name(), token});
        }

    private:

        std::shared_ptr<IUserRepository> _userRepo;
        std::shared_ptr<IPasswordHasher> _hasher;
        std::shared_ptr<ISessionService> _sessionService;
};