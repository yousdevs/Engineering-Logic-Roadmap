#pragma once

#include <stdexcept>
#include <string>

class PinCode {

    public:

        // Throws std::invalid_argument if any invariant is violated.
        static PinCode from(const std::string& rawPin);

        const std::string& value() const;

        bool operator==(const PinCode& other) const;
        bool operator!=(const PinCode& other) const;

    private:

        explicit PinCode(std::string rawPin);

        std::string _value;
};