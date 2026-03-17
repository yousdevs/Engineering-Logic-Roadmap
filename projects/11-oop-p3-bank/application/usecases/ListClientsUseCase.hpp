#pragma once

#include "domain/repositories/IClientRepository.hpp"
#include "domain/security/Permissions.hpp"

#include "application/common/UseCaseResult.hpp"
#include "application/context/ExecutionContext.hpp"
#include "application/dto/ListClientsRequest.hpp"
#include "application/dto/ListClientsResponse.hpp"
#include "application/usecases/UseCase.hpp"

class ListClientsUseCase : public UseCase {

    private:

        IClientRepository& _clientRepo;

    public:

        ListClientsUseCase(IClientRepository&           clientRepo,
                           const IAuthorizationService& authorizationService)
            : UseCase(authorizationService), _clientRepo(clientRepo) {}

        UseCaseResult<ListClientsResponse> execute(const ExecutionContext&   ctx,
                                                   const ListClientsRequest& request) {

            auto permissionResult = checkPermission(ctx, Permission::ListClients);

            if (!permissionResult.isSuccess()) {

                return UseCaseResult<ListClientsResponse>::failure(permissionResult.message());
            }

            auto clients = _clientRepo.findAll();

            ListClientsResponse response;

            for (const auto& client : clients) {

                response.clients.push_back(
                    {client.getAccountId(), client.getFullName(), client.getBalance()});
            }

            return UseCaseResult<ListClientsResponse>::success(std::move(response));
        }
};