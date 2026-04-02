#pragma once
#include "domain/ports/IPinCodeGenerator.hpp"

// Generates cryptographically random 4-digit PinCodes.
// Skips forbidden values (PinCode invariants) transparently.

class RandomPinCodeGenerator : public IPinCodeGenerator {

    public:

        PinCode generate() override;
};