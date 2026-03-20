#pragma once

#include <ctime>
#include <optional>
#include <stdexcept>
#include <string>

#include "domain/ports/IPinCodeGenerator.hpp"
#include "domain/value_objects/ClientId.hpp"
#include "domain/value_objects/PinCode.hpp"

//  Client — a registered bank customer.
//           Owns identity and authentication credentials.
//
//  Soft delete:
//    deletedAt is absent (nullopt) for active clients.
//    deletedAt is present (timestamp) for deleted clients.

class Client {

    public:

        // Throws std::invalid_argument for any empty field.
        static Client create(ClientId           id,
                             const std::string& firstName,
                             const std::string& lastName,
                             const std::string& phone,
                             PinCode            pinCode);

        static Client reconstitute(ClientId                   id,
                                   std::string                firstName,
                                   std::string                lastName,
                                   std::string                phone,
                                   PinCode                    pinCode,
                                   std::time_t                createdAt,
                                   std::optional<std::time_t> deletedAt);

        // Throws std::logic_error if already deleted.
        void softDelete();

        bool isDeleted() const;

        // Throws std::logic_error if Client is deleted.
        PinCode changePin(IPinCodeGenerator& pinCodeGenerator);

        // Throws std::invalid_argument if phone is empty.
        // Throws std::logic_error if Client is deleted.
        void updatePhone(const std::string& phone);

        const ClientId&            id() const;
        const std::string&         firstName() const;
        const std::string&         lastName() const;
        const std::string&         phone() const;
        const PinCode&             pinCode() const;
        std::time_t                createdAt() const;
        std::optional<std::time_t> deletedAt() const;

    private:

        Client(ClientId                   id,
               std::string                firstName,
               std::string                lastName,
               std::string                phone,
               PinCode                    pinCode,
               std::time_t                createdAt,
               std::optional<std::time_t> deletedAt);

        ClientId                   _id;
        std::string                _firstName;
        std::string                _lastName;
        std::string                _phone;
        PinCode                    _pinCode;  // mutable - replaced by changePin()
        std::time_t                _createdAt;
        std::optional<std::time_t> _deletedAt;
};