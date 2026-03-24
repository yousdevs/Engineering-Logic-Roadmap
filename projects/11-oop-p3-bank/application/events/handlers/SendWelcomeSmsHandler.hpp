#pragma once

#include <memory>

#include "domain/ports/IIdGenerator.hpp"

#include "application/events/IDomainEventHandler.hpp"
#include "application/events/domain/ClientRegisteredEvent.hpp"
#include "application/outbox/IOutboxRepository.hpp"
#include "application/outbox/OutboxEntry.hpp"
#include "application/tasks/defenitions/SendSmsTask.hpp"

// Handles ClientRegisteredEvent.
// Writes a SendSmsTask OutboxEntry inside the active transaction.
// Does Not call INotificationService directly - that is the OutboxPoller's job.
// The outbox write is atomic with the Client/Account saves - guaranteed delivery.

class SendWelcomeSmsHandler : public IDomainEventHandler<ClientRegisteredEvent> {

    public:

        SendWelcomeSmsHandler(std::shared_ptr<IOutboxRepository> outboxRepo,
                              std::shared_ptr<IIdGenerator>      idGenerator)
            : _outboxRepo(std::move(outboxRepo)), _idGenerator(std::move(idGenerator)) {}

        void handle(const ClientRegisteredEvent& event) override {

            SendSmsTask task;
            task.phone = event.phone();
            task.message =
                "Welcome! Your PIN is: " + event.pinCode() + ". Change it on first login.";
            task.clientId = event.clientId();

            OutboxEntry entry;
            entry.id         = _idGenerator->generate();  // not sure if entry.id = event.id
            entry.eventType  = task.taskType();
            entry.payload    = task.serialize();
            entry.occurredAt = event.occurredAt();

            _outboxRepo->save(entry);  // inside the active transaction
        }

    private:

        std::shared_ptr<IOutboxRepository> _outboxRepo;
        std::shared_ptr<IIdGenerator>      _idGenerator;
};