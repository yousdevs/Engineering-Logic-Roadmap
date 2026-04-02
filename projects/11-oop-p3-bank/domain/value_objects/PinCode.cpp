#include "domain/value_objects/PinCode.hpp"

#include <cctype>

PinCode::PinCode(std::string rawPin) : _value(std::move(rawPin)) {}

static void validateLength(const std::string& pin) {

    if (pin.size() != 4)
        throw std::invalid_argument(
            "PinCode: must be exactly 4 digits. "
            "Received length: "
            + std::to_string(pin.size()) + ".");
}

static void validateDigitsOnly(const std::string& pin) {

    for (char c : pin) {

        if (!std::isdigit(static_cast<unsigned char>(c)))
            throw std::invalid_argument(
                "PinCode: must contain digits only (0-9). "
                "Invalid character: '"
                + std::string(1, c) + "'.");
    }
}

static void validateNotAllZeros(const std::string& pin) {

    if (pin == "0000")
        throw std::invalid_argument("PinCode: '0000' is not allowed - trivially guessable.");
}

static void validateNotSequential(const std::string& pin) {

    // check sequential run: 1234, 4567
    bool ascending = true;
    for (std::size_t i = 1; i < pin.size(); ++i) {

        if (pin[i] - pin[i - 1] != 1) {
            ascending = false;
            break;
        }
    }
    if (ascending)
        throw std::invalid_argument(
            "PinCode: '" + pin + "' is not allowed - "
            "ascending sequential pins are trivially guessable."
        );

    // check descending sequential run: 9876, 8765
    bool descending = true;
    for (std::size_t i = 1; i < pin.size(); ++i) {

        if (pin[i - 1] - pin[i] != 1) {

            descending = false;
            break;
        }
    }

    if (descending)
        throw std::invalid_argument(
            "PinCode: '" + pin + "' is not allowed — "
            "descending sequential pins are trivially guessable."
        );
}

PinCode PinCode::from(const std::string& rawPin) {

    validateLength(rawPin);
    validateDigitsOnly(rawPin);
    validateNotAllZeros(rawPin);
    validateNotSequential(rawPin);

    return PinCode(rawPin);
}

const std::string& PinCode::value() const {
    return _value;
}

bool PinCode::operator==(const PinCode& other) const {
    return _value == other._value;
}

bool PinCode::operator!=(const PinCode& other) const {
    return !(*this == other);
}
