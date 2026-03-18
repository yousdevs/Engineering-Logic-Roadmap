#pragma once

#include "domain/ports/IPinCodeGenerator.hpp"

// This implementation For Tests use.

class SequentialPinCodeGenerator : public IPinCodeGenerator {

    public:

        // Throws std::invalid_argument if seed is not a 4 digits.
        explicit SequentialPinCodeGenerator(const std::string& seed = "2000");

        // Returns the next valid PinCode in sequence
        PinCode generate() override;

        // Returns how many times generate() has been called.
        int callCount() const;

    private:

        int _current;
        int _callCount;

        // Advances _current to the next integer
        void advance();

        // Returns true if the given 4 digit zero-padded
        // integer would be rejected by PinCode::from().
        bool isForbidden(int value) const;

        // Formats an integer as a zero-padded 4 char string.
        static std::string format(int value);
};