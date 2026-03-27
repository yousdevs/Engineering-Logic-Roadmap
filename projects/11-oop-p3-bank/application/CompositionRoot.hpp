#pragma once

#include <memory>

// Application abstractions
#include "application/abstractions/PipelineBuilder.hpp"
#include "application/abstractions/UseCasePipeline.hpp"
#include "application/events/EventDispatcher.hpp"
#include "application/events/handlers/SendWelcomeSmsHandler.hpp"

// Use cases
#include "application/usecases/client/RegisterClientUseCase.hpp"
#include "application/usecases/currency/GetCurrencyRateUseCase.hpp"
#include "application/usecases/user/LoginUseCase.hpp"

// Infrastructure ports (injected - not created here)
#include "domain/ports/IIdGenerator.hpp"
#include "domain/ports/IPasswordHasher.hpp"
#include "domain/ports/IPinCodeGenerator.hpp"
#include "domain/ports/IUnitOfWork.hpp"
#include "domain/repositories/IAccountRepository.hpp"
#include "domain/repositories/IClientRepository.hpp"
#include "domain/repositories/IUserRepository.hpp"

#include "application/audit/IAuditLog.hpp"
#include "application/outbox/IOutboxPoller.hpp"
#include "application/outbox/IOutboxRepository.hpp"
#include "application/services/ICurrencyRateService.hpp"
#include "application/services/INotificationService.hpp"
#include "application/services/IRateLimiter.hpp"
#include "application/services/ISessionService.hpp"
#include "application/tasks/ITaskQueue.hpp"

// All assembled pipelines exposed to the presentation layer.
struct ApplicationPipelines {

        UseCasePipeline<LoginRequest, LoginResponse>                     login;
        UseCasePipeline<RegisterClientRequest, RegisterClientResponse>   registerClient;
        UseCasePipeline<GetCurrencyRateRequest, GetCurrencyRateResponse> currencyRate;
};

// Single wiring point - the C++ equivalent of a NestJS AppModule.
// Nothing outside this file calls new() on application or domain objects.
// To add a use case: implement it with metadata(), add one build() call here.

class CompositionRoot {

    public:

        ApplicationPipelines           pipelines;
        std::shared_ptr<IOutboxPoller> outboxPoller;
        std::shared_ptr<ITaskQueue>    taskQueue;

        static CompositionRoot build(

            std::shared_ptr<IUserRepository>      userRepo,
            std::shared_ptr<IClientRepository>    clientRepo,
            std::shared_ptr<IAccountRepository>   accountRepo,
            std::shared_ptr<IOutboxRepository>    outboxRepo,
            std::shared_ptr<IUnitOfWork>          unitOfWork,
            std::shared_ptr<IAuditLog>            auditLog,
            std::shared_ptr<IIdGenerator>         idGenerator,
            std::shared_ptr<IPinCodeGenerator>    pinGenerator,
            std::shared_ptr<IPasswordHasher>      hasher,
            std::shared_ptr<ISessionService>      sessionService,
            std::shared_ptr<ICurrencyRateService> currencyRateService,
            std::shared_ptr<IRateLimiter>         rateLimiter,
            std::shared_ptr<ITaskQueue>           taskQueue,
            std::shared_ptr<IOutboxPoller>        outboxPoller,
            std::shared_ptr<INotificationService> notificationService) {

            // Task handlers
            taskQueue->registerHandler("SendSmsTask",
                                       [notificationService](const std::string& payload) {
                                           // parse payload -> notificationService->sendSms(..)
                                           // TODO: Replace with nlohmann/json deserialization.
                                       });

            // Event dispatcher + handlers
            auto dispatcher     = std::make_shared<EventDispatcher>();
            auto welcomeHandler = std::make_shared<SendWelcomeSmsHandler>(outboxRepo, idGenerator);

            dispatcher->registerHandler(
                "ClientRegisteredEvent", [welcomeHandler](const IDomainEvent& e) {
                    welcomeHandler->handle(static_cast<const ClientRegisteredEvent&>(e));
                });

            // pipeline services
            PipelineServices services{auditLog, unitOfWork, rateLimiter};

            // Pipelines
            // PipelineBuilder reads each use case's metadata() and wires
            // only the interceptors the use case declared it needs.

            auto loginPipeline = PipelineBuilder::build<LoginRequest, LoginResponse>(
                std::make_shared<LoginUseCase>(userRepo, hasher, sessionService), services);
            // metadata: asPublic, readOnly, rateLimited, audited
            // chain: CallerPolicy -> Validation -> RateLimit -> Audit

            auto registerClientPipeline =
                PipelineBuilder::build<RegisterClientRequest, RegisterClientResponse>(
                    std::make_shared<RegisterClientUseCase>(
                        clientRepo, accountRepo, idGenerator, pinGenerator, dispatcher),
                    services);
            // metadata: requiresAuth, Permission::AddClient, transactional, audited
            // chain: CallerPolicy -> Validation -> Auth -> Audit -> Transaction

            auto currencyRatePipeline =
                PipelineBuilder::build<GetCurrencyRateRequest, GetCurrencyRateResponse>(
                    std::make_shared<GetCurrencyRateUseCase>(currencyRateService), services);
            // metadata: asPublic, readOnly, noAudit, rateLimited
            // chain: CallerPolicy -> Validation -> RateLimit

            CompositionRoot root{ApplicationPipelines{std::move(loginPipeline),
                                                      std::move(registerClientPipeline),
                                                      std::move(currencyRatePipeline)},
                                 outboxPoller,
                                 taskQueue};

            taskQueue->start();
            outboxPoller->start();

            return root;
        }

        void shutdown() {

            if (outboxPoller)
                outboxPoller->stop();

            if (taskQueue)
                taskQueue->stop();
        }
};