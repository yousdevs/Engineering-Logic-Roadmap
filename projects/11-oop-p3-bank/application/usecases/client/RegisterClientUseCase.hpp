#pragma once

#include <memory>
#include <string>

#include "domain/entities/Account.hpp"
#include "domain/entities/Client.hpp"
#include "domain/ports/IIdGenerator.hpp"
#include "domain/ports/IPinCodeGenerator.hpp"
#include "domain/repositories/IAccountRepository.hpp"
#include "domain/repositories/IClientRepository.hpp"
#include "domain/security/Permissions.hpp"

#include "application/abstractions/IUseCase.hpp"
#include "application/events/IEventDispatcher.hpp"
#include "application/events/domain/ClientRegisteredEvent.hpp"

struct RegisterClientRequest : UseCaseRequest {

        std::string firstName;
        std::string lastName;
        std::string phone;

        std::vector<ValidationError> validate() const override {

            std::vector<ValidationError> errors;

            if (firstName.empty())
                errors.push_back({"firstName", "Required."});

            if (lastName.empty())
                errors.push_back({"lastName", "Required."});

            if (phone.empty())
                errors.push_back({"phone", "Required."});

            return errors;
        }
};

struct RegisterClientResponse : UseCaseResponse {

        std::string clientId;
        std::string accountId;
        // pinCode absent - delivered via SMS (outbox -> SMS task)

        RegisterClientResponse(std::string clientId, std::string accountId)
            : clientId(std::move(clientId)), accountId(std::move(accountId)) {}
};

// Authenticated (Permission::AddClient), transactional, audited.
// Orchestrates Client + Account creation atomically.
// Dispatches ClientRegisteredEvent - handler writes SendSmsTask to outbox.
// The outbox write is inside the same transaction as the entity saves.

class RegisterClientUseCase : public IUseCase<RegisterClientRequest, RegisterClientResponse> {

    public:

        RegisterClientUseCase(std::shared_ptr<IClientRepository>  clientRepo,
                              std::shared_ptr<IAccountRepository> accountRepo,
                              std::shared_ptr<IIdGenerator>       idGenerator,
                              std::shared_ptr<IPinCodeGenerator>  pinGenerator,
                              std::shared_ptr<IEventDispatcher>   eventDispatcher)
            : _clientRepo(std::move(clientRepo))
            , _accountRepo(std::move(accountRepo))
            , _idGenerator(std::move(idGenerator))
            , _pinGenerator(std::move(pinGenerator))
            , _eventDispatcher(std::move(eventDispatcher)) {}

        UseCaseMetadata metadata() const override {

            return UseCaseMetadata::create("RegisterClient").withPermission(Permission::AddClient);
        }

        UseCaseResult<RegisterClientResponse> execute(
            const ExecutionContext& ctx, const RegisterClientRequest& request) override {

            if (_clientRepo->existsByPhone(request.phone))
                return UseCaseResult<RegisterClientResponse>::fail(AppError::conflict(
                    "A client with phone '" + request.phone + "' already exists."));

            auto clientId  = ClientId::generate(*_idGenerator);
            auto accountId = AccountId::generate(*_idGenerator);
            auto pinCode   = _pinGenerator->generate();
            auto eventId   = _idGenerator->generate();

            auto client = Client::create(
                clientId, request.firstName, request.lastName, request.phone, pinCode);

            auto account = Account::openFor(accountId, clientId);

            _clientRepo->save(client);
            _accountRepo->save(account);

            // Dispatched inside the transaction - handler writes outbox entry.
            _eventDispatcher->dispatch(
                ClientRegisteredEvent{eventId, clientId.value(), request.phone, pinCode.value()});

            return UseCaseResult<RegisterClientResponse>::ok({clientId.value(), accountId.value()});
        }

    private:

        std::shared_ptr<IClientRepository>  _clientRepo;
        std::shared_ptr<IAccountRepository> _accountRepo;
        std::shared_ptr<IIdGenerator>       _idGenerator;
        std::shared_ptr<IPinCodeGenerator>  _pinGenerator;
        std::shared_ptr<IEventDispatcher>   _eventDispatcher;
};