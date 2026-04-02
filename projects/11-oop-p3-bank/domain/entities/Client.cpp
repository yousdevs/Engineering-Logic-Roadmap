#include "domain/entities/Client.hpp"

Client::Client(ClientId                   id,
               std::string                firstName,
               std::string                lastName,
               std::string                phone,
               PinCode                    pinCode,
               std::time_t                createdAt,
               std::optional<std::time_t> deletedAt)
    : _id(std::move(id))
    , _firstName(std::move(firstName))
    , _lastName(std::move(lastName))
    , _phone(std::move(phone))
    , _pinCode(std::move(pinCode))
    , _createdAt(createdAt)
    , _deletedAt(deletedAt) {}

// File-socpe shared validation helper
static void requireNonEmpty(const std::string& value,
                            const std::string& fieldName,
                            const std::string& context) {

    if (value.empty())
        throw std::invalid_argument(context + ": " + fieldName + " cannot be empty.");
}

Client Client::create(ClientId           id,
                      const std::string& firstName,
                      const std::string& lastName,
                      const std::string& phone,
                      PinCode            pinCode) {

    requireNonEmpty(firstName, "firstName", "Client::create");
    requireNonEmpty(lastName, "lastName", "Client::create");
    requireNonEmpty(phone, "phone", "Client::create");

    return Client(std::move(id),
                  firstName,
                  lastName,
                  phone,
                  std::move(pinCode),
                  std::time(nullptr),
                  std::nullopt);
}

Client Client::reconstitute(ClientId                   id,
                            std::string                firstName,
                            std::string                lastName,
                            std::string                phone,
                            PinCode                    pinCode,
                            std::time_t                createdAt,
                            std::optional<std::time_t> deletedAt) {

    // data was valid when originally saved.
    return Client(std::move(id),
                  std::move(firstName),
                  std::move(lastName),
                  std::move(phone),
                  std::move(pinCode),
                  createdAt,
                  deletedAt);
}

void Client::softDelete() {

    if (_deletedAt.has_value())
        throw std::logic_error("Client [" + _id.value() + "] is already deleted.");

    _deletedAt = std::time(nullptr);
}

bool Client::isDeleted() const {
    return _deletedAt.has_value();
}

PinCode Client::changePin(IPinCodeGenerator& pinCodeGenerator) {

    if (_deletedAt.has_value())
        throw std::logic_error("Cannot change Pin for deleted client: [" + _id.value() + "].");

    _pinCode = pinCodeGenerator.generate();
    return _pinCode;
}

void Client::updatePhone(const std::string& phone) {

    if (_deletedAt.has_value())
        throw std::logic_error("Cannot update phone for client [" + _id.value() + "].");

    requireNonEmpty(phone, "phone", "Client::updatePhone");
    _phone = phone;
}

const ClientId& Client::id() const {
    return _id;
}
const std::string& Client::firstName() const {
    return _firstName;
}
const std::string& Client::lastName() const {
    return _lastName;
}
const std::string& Client::phone() const {
    return _phone;
}
const PinCode& Client::pinCode() const {
    return _pinCode;
}
std::time_t Client::createdAt() const {
    return _createdAt;
}
std::optional<std::time_t> Client::deletedAt() const {
    return _deletedAt;
}