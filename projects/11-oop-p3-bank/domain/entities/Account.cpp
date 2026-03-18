
#include "domain/entities/Account.hpp"

Account::Account(AccountId id, ClientId clientId, AccountStatus status, std::time_t createdAt)
    : _id(std::move(id)), _clientId(std::move(clientId)), _status(status), _createdAt(createdAt) {}

Account Account::openFor(AccountId id, const ClientId& clientId) {

    return Account(std::move(id), clientId, AccountStatus::ACTIVE, std::time(nullptr));
}

Account Account::reconstitute(AccountId     id,
                              ClientId      clientId,
                              AccountStatus status,
                              std::time_t   createdAt) {

    return Account(std::move(id), std::move(clientId), status, createdAt);
}

void Account::freeze() {

    if (_status == AccountStatus::CLOSED)
        throw std::logic_error("Cannot freeze account [" + _id.value() + "]: "
            "account is CLOSED. CLOSED is a terminal state.");

    if (_status == AccountStatus::FROZEN)
        throw std::logic_error("Cannot freeze account [" + _id.value() + "]: "
            "account is already FROZEN.");

    _status = AccountStatus::FROZEN;
}

void Account::unfreeze() {

    if (_status == AccountStatus::CLOSED)
        throw std::logic_error("Cannot unfreeze account [" + _id.value() + "]: "
            "account is CLOSED. CLOSED is a terminal state.");

    if (_status == AccountStatus::ACTIVE)
        throw std::logic_error(
            "Cannot unfreeze account [" + _id.value() + "]: "
            "account is already ACTIVE."
        );

    _status = AccountStatus::ACTIVE;
}

void Account::close() {

    if (_status == AccountStatus::CLOSED)
        throw std::logic_error("Cannot close account [" + _id.value() + "]: "
            "account is already CLOSED.");

    // Both ACTIVE and Frozen can be CLOSED
    _status = AccountStatus::CLOSED;
}

const AccountId& Account::id() const {
    return _id;
}

const ClientId& Account::clientId() const {
    return _clientId;
}

AccountStatus Account::status() const {
    return _status;
}

std::time_t Account::createdAt() const {
    return _createdAt;
}

bool Account::isActive() const {
    return _status == AccountStatus::ACTIVE;
}

bool Account::isFrozen() const {
    return _status == AccountStatus::FROZEN;
}

bool Account::isClosed() const {
    return _status == AccountStatus::CLOSED;
}