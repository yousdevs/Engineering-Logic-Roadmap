#include "infrastructure/security/SequentialPinCodeGenerator.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

//  PinCode::from() is the source of truth for what is forbidden.
//  isForbidden() mirrors those rules internally so the generator
//  can skip ahead without calling PinCode::from() in a loop
//  and catching exceptions

SequentialPinCodeGenerator::SequentialPinCodeGenerator(const std::string& seed) : _callCount(0) {

    if (seed.size() != 4)
        throw std::invalid_argument(
            "SequentialPinCodeGenerator: seed must be exactly "
            "4 digits. Received: '"
            + seed + "'.");

    for (char c : seed) {

        if (c < '0' || c > '9')
            throw std::invalid_argument(
                "SequentialPinCodeGenerator: seed must contain "
                "digits only. Received: '"
                + seed + "'.");
    }

    _current = std::stoi(seed);

    while (isForbidden(_current))
        advance();
}

PinCode SequentialPinCodeGenerator::generate() {

    PinCode pin = PinCode::from(format(_current));

    ++_callCount;

    advance();
    while (isForbidden(_current))
        advance();

    return pin;
}

int SequentialPinCodeGenerator::callCount() const {
    return _callCount;
}

void SequentialPinCodeGenerator::advance() {

    ++_current;

    if (_current > 9999)
        _current = 1;
}

// mirrors PinCode invariants, this avoids exceptions control flow
bool SequentialPinCodeGenerator::isForbidden(int value) const {

    if (value == 0)
        return true;

    int d0 = (value / 1000) % 10;
    int d1 = (value / 100) % 10;
    int d2 = (value / 10) % 10;
    int d3 = (value / 1) % 10;

    // Rule 2: ascending sequential (each digit = previous + 1).
    if (d1 == d0 + 1 && d2 == d1 + 1 && d3 == d2 + 1)
        return true;

    // Rule 3: descending sequential (each digit = previous - 1).
    if (d1 == d0 - 1 && d2 == d1 - 1 && d3 == d2 - 1)
        return true;

    return false;
}

std::string SequentialPinCodeGenerator::format(int value) {

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << value;
    return oss.str();
}