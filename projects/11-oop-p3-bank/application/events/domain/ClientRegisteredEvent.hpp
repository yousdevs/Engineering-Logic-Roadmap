#pragma once

#include <ctime>
#include <string>

#include "application/events/IDomainEvent.hpp"

// Raised by RegisterClientUseCase after Client + Account are saved.
// Carries data handlers need without reloading from the DB.
// pinCode is included for the welcome SMS only - not for HTTP responses.

class ClientRegisteredEvent : public IDomainEvent {

    public:

        ClientRegisteredEvent(std::string eventId,
                              std::string clientId,
                              std::string phone,
                              std::string pinCode)
            : _eventId(std::move(eventId))
            , _clientId(std::move(clientId))
            , _phone(std::move(phone))
            , _pinCode(std::move(pinCode))
            , _occurredAt(std::time(nullptr)) {}

        std::string eventType() const override {
            return "ClientRegisteredEvent";
        }

        std::string eventId() const override {
            return _eventId;
        }

        std::time_t occurredAt() const override {
            return _occurredAt;
        }

        const std::string& clientId() const {
            return _clientId;
        }

        const std::string& phone() const {
            return _phone;
        }

        const std::string& pinCode() const {
            return _pinCode;
        }

    private:

        std::string _eventId;
        std::string _clientId;
        std::string _phone;
        std::string _pinCode;
        std::time_t _occurredAt;
};